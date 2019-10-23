// This is the js for the default/index.html view.


var app = function () {

    var self = {};

    Vue.config.silent = false; // show all warnings

    // Extends an array
    self.extend = function (a, b) {
        for (var i = 0; i < b.length; i++) {
            a.push(b[i]);
        }
    };

    // Enumerates an array.
    var enumerate = function (v) { var k = 0; return v.map(function (e) { e._idx = k++; }); };

    self.open_uploader = function () {
        $("div#uploader_div").show();
        self.vue.is_uploading = true;
    };

    self.close_uploader = function () {
        $("div#uploader_div").hide();
        self.vue.is_uploading = false;
        $("input#file_input").val(""); // This clears the file choice once uploaded.

    };


    // set user info if a user is logged in
    self.user_info = function () {
        // get if a user is logged in and if so what the email is
        $.getJSON(user_info_URL,
            function (data) {
                self.vue.logged_in = data.logged_in;
                self.vue.logged_in_user_email = data.logged_in_user_email;
                self.vue.user_has_image = data.user_has_image;
            }
        );
    }

    //create list of users that have at least one image 
    self.set_user_list = function () {
        // set the list of users 
        $.getJSON(set_user_list_URL,
            function (data) {
                self.vue.user_list = [];
                self.vue.user_list = data.user_list;
            }
        );
    }


    //stuff to upload file
    self.upload_file = function (event) {
        // Reads the file.

        var input = $("input#file_input")[0]
        var file = input.files[0];
        var reader = new FileReader();

        reader.addEventListener("load", function () {
            self.vue.img_url = reader.result;
        }, false);

        if (file) {
            reader.readAsDataURL(file);
            // Gets an upload URL.
            console.log("Trying to get the upload url");
            $.getJSON('https://upload-dot-luca-teaching.appspot.com/start/uploader/get_upload_url',
                function (data) {
                    // We now have upload (and download) URLs.
                    var put_url = data['signed_url'];
                    var get_url = data['access_url'];
                    console.log("Received upload url: " + put_url);
                    // Uploads the file, using the low-level interface.
                    var req = new XMLHttpRequest();
                    req.addEventListener("load", self.upload_complete(get_url));
                    // TODO: if you like, add a listener for "error" to detect failure.
                    req.open("PUT", put_url, true);
                    req.send(file);
                });
        }
    };


    self.upload_complete = function (get_url) {
        // Hides the uploader div.
        self.vue.show_img = true;
        self.close_uploader();
        console.log('The file was uploaded; it is now available at ' + get_url);

        //get price from the input 
        var input = $("input#price_input")[0]
        var price_value = input.valueAsNumber;
        input.value = null; //clear the input
        console.log(price_value);

        // add the image to the database
        $.post(add_image_URL,
            {
                get_url: get_url,
                price: price_value
            },
            function (data) {
                self.vue.last_added_image_id = data.iID;
                self.vue.last_added_image_url = data.image_url;

                // wait 750 millisec to update the list for the uploader/logged in user and then re-get the images
                //update your own page (you must be on your own page to upload, so you konw you are on the logged in user's page)
                setTimeout(self.get_user_images, 750, self.vue.logged_in_user_email);

                if (self.vue.user_has_image <= 0) {
                    self.set_user_list();
                    self.vue.user_has_image = true
                }
            }
        );

    };

    //methods for images 
    self.get_user_images = function (selected_email) {
        // for the user, set vue.images to the users images
        // if selected email is the one logged in, set self_image to true

        self.vue.self_page = (selected_email == self.vue.logged_in_user_email);

        $.getJSON(get_images_URL,
            {
                // pass parameter of which user's email was selected
                selected_email: selected_email,
            },
            function (data) {
                // for every image, add image url to vue.images
                self.vue.images = data.user_image_urls;
                enumerate(self.vue.images)
            }
        );
    }

    // methods for price
    self.edit_price = function (image_index) {
        //toggle it to being edited
        $.post(edit_image_price_URL,
            {
                image_ID: self.vue.images[image_index].id
            },
            function (data) {
                self.vue.images[image_index].being_edited = data.new_status
            }

        );
    }

    self.set_price = function (image_index, new_price) {

        //toggled it back to not being edited
        $.post(set_image_price_URL,
            {
                image_ID: self.vue.images[image_index].id,
                new_price: new_price
            },
            function (data) {
                self.vue.images[image_index].being_edited = data.new_status
            }

        );
    }


    // methods for cart 
    self.add_to_cart = function (image_ID, flag = true) {
        // flag is default to true to indicate that the image
        // should actually be added to the cart. 
        // the check icon also comes to this method but with flag=false

        if (flag) {
            self.vue.ids_in_cart.push(image_ID);

            //get urls for the id
            $.getJSON(image_url_to_cart_URL,
                {
                    image_ID: image_ID,
                    total_sum_so_far: self.vue.total_sum,
                },
                function (data) {
                    self.vue.cart.push(data.image_info)
                    self.vue.total_sum = data.new_total
                }
            );
        } else {
            alert("Image is already in the cart")
        }

    }

    self.add_to_cart_not_logged_in = function () {
        alert("Must be logged in to add an item to your cart")
    }

    self.go_checkout = function () {
        //go to checkout view
        self.vue.is_checkout = true;
        self.goto('cart');
    }

    self.go_back = function () {
        // self.vue.total_sum = 0;
        self.vue.is_checkout = false;
    }

    self.customer_info = {}

    self.goto = function (page) {
        self.vue.page = page;
        if (page == 'cart') {
            // prepares the form.
            self.stripe_instance = StripeCheckout.configure({
                key: 'pk_test_FF1fziytNqRluZ6jegNUEofi',
                image: 'https://stripe.com/img/documentation/checkout/marketplace.png',
                locale: 'auto',
                token: function (token, args) {
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
            amount: self.vue.total_sum * 100,
        });
    };

    self.send_data_to_server = function () {
        console.log("Payment for:", self.customer_info);
        // Calls the server.
        $.post(purchase_URL,
            {
                customer_info: JSON.stringify(self.customer_info),
                transaction_token: JSON.stringify(self.stripe_token),
                amount: self.vue.total_sum,
                cart: JSON.stringify(self.vue.cart),
            },
            function (data) {
                // The order was successful.
                self.vue.cart = [];
                self.vue.ids_in_cart = [];
                self.vue.total_sum = 0;
                self.goto('prod');
                $.web2py.flash("Thank you for your purchase");
            }
        );
    };

    self.vue = new Vue({
        el: "#vue-div",
        delimiters: ['${', '}'],
        unsafeDelimiters: ['!{', '}'],
        data: {
            is_uploading: false,
            img_url: null,
            show_img: false,
            self_page: true, // Leave it to true, so initially you are looking at your own images.

            logged_in_user_email: null,
            logged_in: false,
            user_has_image: false, //assume the logged in user has no images (gets updated in user_info)
            last_added_image_url: null,
            last_added_image_id: null,
            images: [],
            user_list: [],
            editing_price: false,
            ids_in_cart: [], //just ids of the images
            cart: [], // the ids, urls, user, etc
            is_checkout: false,
            total_sum: 0,
            page: 'prod',


        },
        methods: {
            open_uploader: self.open_uploader,
            close_uploader: self.close_uploader,
            upload_file: self.upload_file,

            user_info: self.user_info,
            get_user_images: self.get_user_images,
            set_user_list: self.set_user_list,
            set_price: self.set_price,
            edit_price: self.edit_price,
            add_to_cart: self.add_to_cart,
            add_to_cart_not_logged_in: self.add_to_cart_not_logged_in,
            go_checkout: self.go_checkout,
            go_back: self.go_back,
            pay: self.pay,
        }

    });

    self.user_info(); // get if there is a user logged in and if so, what the email is 
    self.set_user_list(); // set the list of all users in the database
    // console.log(self.vue.logged_in_user_email);
    // setTimeout(console.log, 5000, self.vue.logged_in_user_email)
    // self.get_user_images(self.vue.logged_in_user_email);
    $("#vue-div").show();

    return self;
};

var APP = null;

// This will make everything accessible from the js console;
// for instance, self.x above would be accessible as APP.x
jQuery(function () { APP = app(); });

