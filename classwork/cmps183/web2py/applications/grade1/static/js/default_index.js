// This is the js for the default/index.html view.

var app = function() {

    var self = {};

    Vue.config.silent = false; // show all warnings

    // Extends an array
    self.extend = function(a, b) {
        for (var i = 0; i < b.length; i++) {
            a.push(b[i]);
        }
    };

    // Enumerates an array.
    var enumerate = function(v) {
        var k=0;
        return v.map(function(e) {e._idx = k++;});
    };

    self.open_uploader = function () {
        $("div#uploader_div").show();
        self.vue.is_uploading = true;
    };

    self.close_uploader = function () {
        $("div#uploader_div").hide();
        self.vue.is_uploading = false;
        $("input#file_input").val(""); // This clears the file choice once uploaded.
    };

    self.upload_file = function (event) {
      console.log(event.target);
        // Reads the file.
        var input = event.target;
        var file = input.files[0];
        if (file) {
            // First, gets an upload URL.
            console.log("Trying to get the upload url");
            $.getJSON('https://upload-dot-luca-teaching.appspot.com/start/uploader/get_upload_url',
                function (data) {
                    // We now have upload (and download) URLs.
                    var put_url = data['signed_url'];
                    var get_url = data['access_url'];
                    //console.log("Received upload url: " + put_url);
                    console.log(get_url);
                    // Uploads the file, using the low-level interface.
                    var req = new XMLHttpRequest();
                    req.addEventListener("load", self.upload_complete(get_url));
                    // TODO: if you like, add a listener for "error" to detect failure.
                    req.open("PUT", put_url, true);
                    req.send(file);
                });
        }
    };


    self.upload_complete = function(get_url, price) {
        // Hides the uploader div.
        self.close_uploader();
        console.log('The file was uploaded; it is now available at ' + get_url);
        $.post(add_image_url,
            {
                image_url: get_url,
                price: price
            },
            function (data){
                enumerate(self.vue.image_list);
                console.log("Good!!!");
            }
        )
    };


    function get_images_url(start_idx, end_idx, email){
        console.log("HELLO");
        var pp = {
            start_idx: start_idx,
            end_idx: end_idx,
            email: email
        };
        return images_url + "&" + $.param(pp);
    };

    self.get_images = function(email){
        console.log("Trying to get the user_images");
        console.log(email)
        $.getJSON(get_images_url(0, 20, email), function (data){
            console.log(data);
            self.vue.image_list = data.image_list;
            enumerate(self.vue.image_list);
        })
    };


    self.get_user_list = function(){
        console.log("TESTING");
        $.post(get_user_list_url,
            {
            }, function (data){
            self.vue.user_list = data.user_list;
            enumerate(self.vue.user_list);
        })
    };

    self.get_user = function(){
        $.post(get_user_url,
            {
            }, function (data){
            self.vue.user_list2 = data.user_list2;
        })
    };

    self.get_products = function () {
        // Gets new products in response to a query, or to an initial page load.
        $.getJSON(products_url, $.param({q: self.vue.product_search}), function(data) {
            self.vue.carter = data.products;
            enumerate(self.vue.carter);
        });
    };

    self.store_cart = function() {
        localStorage.products = JSON.stringify(self.vue.products);
    };

    self.read_cart = function() {
        if (localStorage.carter) {
            self.vue.products = JSON.parse(localStorage.products);
        } else {
            self.vue.products = [];
        }
        self.update_cart();
    };

    self.inc_desired_quantity = function(product_idx, qty) {
        // Inc and dec to desired quantity.
        var p = self.vue.products[product_idx];
        p.desired_quantity = Math.max(0, p.desired_quantity + qty);
        p.desired_quantity = Math.min(p.quantity, p.desired_quantity);
    };

    self.inc_cart_quantity = function(product_idx, qty) {
        // Inc and dec to desired quantity.
        var p = self.vue.carter[product_idx];
        p.cart_quantity = Math.max(0, p.cart_quantity + qty);
        p.cart_quantity = Math.min(p.quantity, p.cart_quantity);
        self.update_cart();
        self.store_cart();
    };

    self.update_cart = function () {
        enumerate(self.vue.products);
        var cart_size = 0;
        var cart_total = 0;
        for (var i = 0; i < self.vue.products.length; i++) {
            var q = self.vue.products[i].cart_quantity;
            if (q > 0) {
                cart_size++;
                cart_total += q * self.vue.products[i].price;
            }
        }
        self.vue.cart_size = cart_size;
        self.vue.cart_total = cart_total;
    };

    self.buy_product = function(product_idx) {
        var p = self.vue.carter[product_idx];
        // I need to put the product in the cart.
        // Check if it is already there.
        var already_present = false;
        var found_idx = 0;
        for (var i = 0; i < self.vue.carter.length; i++) {
            if (self.vue.carter[i].id === p.id) {
                already_present = true;
                found_idx = i;
            }
        }
        // If it's there, just replace the quantity; otherwise, insert it.
        if (!already_present) {
            found_idx = self.vue.carter.length;
            self.vue.carter.push(p);
        }
        self.vue.carter[found_idx].cart_quantity = p.desired_quantity;

        // Updates the amount of products in the cart.
        self.update_cart();
        self.store_cart();
        console.log("PERFECT");
    };

    self.customer_info = {}

    self.goto = function (page) {
        self.vue.page = page;
        if (page == 'cart') {
            // prepares the form.
            self.stripe_instance = StripeCheckout.configure({
                key: 'pk_test_CeE2VVxAs3MWCUDMQpWe8KcX',    //put your own publishable key here
                image: 'https://stripe.com/img/documentation/checkout/marketplace.png',
                locale: 'auto',
                token: function(token, args) {
                    console.log('got a token. sending data to localhost.');
                    self.stripe_token = token;
                    self.customer_info = args;
                    self.send_data_to_server();
                }
            });
        };

    };

    self.pay = function () {
        self.stripe_instance.open({
            name: "Your nice cart",
            description: "Buy cart content",
            billingAddress: true,
            shippingAddress: true,
            amount: Math.round(self.vue.cart_total * 100),
        });
    };

    self.send_data_to_server = function () {
        console.log("Payment for:", self.customer_info);
        // Calls the server.
        $.post(purchase_url,
            {
                customer_info: JSON.stringify(self.customer_info),
                transaction_token: JSON.stringify(self.stripe_token),
                amount: self.vue.cart_total,
                cart: JSON.stringify(self.vue.cart),
            },
            function (data) {
                if (data.result === "ok") {
                    // The order was successful.
                    self.vue.cart = [];
                    self.update_cart();
                    self.store_cart();
                    self.goto('prod');
                    $.web2py.flash("Thank you for your purchase");
                } else {
                    $.web2py.flash("The card was declined.");
                }
            }
        );
    };

    self.update_price = function (img_idx) {
      $.post(update_price_url, {
        img_id: self.vue.image_list[img_idx].id,
        price: self.vue.image_list[img_idx].price
      });
    };

    self.add_to_cart = function (img_idx) {
        self.vue.image_list[img_idx].in_cart = !self.vue.image_list[img_idx].in_cart;
        $.post(toggle_cart_url, {img_id: self.vue.image_list[img_idx].id});
    };

    self.log_event = function (event) {
        self.vue.curr_event = event;
    };

    self.submit = function(){
      var input = self.vue.curr_event.target;
      var file = input.files[0];
      if (file) {
          // First, gets an upload URL.
          console.log("Trying to get the upload url");
          $.getJSON('https://upload-dot-luca-teaching.appspot.com/start/uploader/get_upload_url',
              function (data) {
                  // We now have upload (and download) URLs.
                  var put_url = data['signed_url'];
                  var get_url = data['access_url'];
                  //console.log("Received upload url: " + put_url);
                  console.log(get_url);
                  // Uploads the file, using the low-level interface.
                  var req = new XMLHttpRequest();
                  req.addEventListener("load", self.upload_complete(get_url, self.vue.curr_price));
                  // TODO: if you like, add a listener for "error" to detect failure.
                  req.open("PUT", put_url, true);
                  req.send(file);
              });
      }
    };

    self.set_price = function(event){
      var input = event.target;
      var text = input.valueAsNumber;
      self.vue.curr_price = text;
    };

    self.vue = new Vue({
        el: "#vue-div",
        delimiters: ['${', '}'],
        unsafeDelimiters: ['!{', '}'],
        data: {
            is_uploading: false,
            self_page: true, // Leave it to true, so initially you are looking at your own images.
            image_list: [],
            user_list: [],
            user_list2: [],
            products: [],
            cart: [],
            carter: [],
            product_search: '',
            price: 0,
            cart_size: 0,
            cart_total: 0,
            page: 'prod',
            in_cart: false,
            curr_event: null,
            curr_price: 0
        },
        methods: {
            open_uploader: self.open_uploader,
            close_uploader: self.close_uploader,
            log_event: self.log_event,
            update_price: self.update_price,
            submit: self.submit,
            set_price: self.set_price,
            upload_file: self.upload_file,
            get_images_url: self.get_images_url,
            get_images: self.get_images,
            get_user_list: self.get_user_list,
            get_user: self.get_user,
            get_products: self.get_products,
            inc_desired_quantity: self.inc_desired_quantity,
            inc_cart_quantity: self.inc_cart_quantity,
            buy_product: self.buy_product,
            goto: self.goto,
            do_search: self.get_products,
            pay: self.pay,
            add_to_cart: self.add_to_cart
        }

    });

    self.get_user();
    self.get_user_list();
    self.get_products();
    self.update_cart();
    self.read_cart();
    $("#vue-div").show();


    return self;
};

var APP = null;

// This will make everything accessible from the js console;
// for instance, self.x above would be accessible as APP.x
jQuery(function(){APP = app();});
