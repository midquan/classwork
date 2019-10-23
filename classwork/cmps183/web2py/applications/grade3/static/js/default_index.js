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
    var enumerate = function(v) { var k=0; return v.map(function(e) {e._idx = k++;});};

    self.open_uploader = function () {
        $("div#uploader_div").show();
        self.vue.is_uploading = true;
    };

    self.close_uploader = function () {
        $("div#uploader_div").hide();
        self.vue.is_uploading = false;
        $("input#file_input").val(""); // This clears the file choice once uploaded.
        $("input#price_input").val("");

    };

    self.upload_file = function (event) {
        // Reads the file.
        //console.log(event);
        var input = event.target;
        var file = document.getElementById("file_input").files[0];
        if (file) {

            // First, gets an upload URL.
            //console.log("Trying to get the upload url");
            $.getJSON('https://upload-dot-luca-teaching.appspot.com/start/uploader/get_upload_url',
                function (data) {
                    // We now have upload (and download) URLs.
                    console.log(data);
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

    self.checkout_pressed = function() {
        console.log("checkout pressed");
        self.vue.is_checkout = !self.vue.is_checkout;

    }


    self.upload_complete = function(get_url) {
        // Hides the uploader div.
        self.close_uploader();
        console.log("Price: " + self.vue.price);
        // TODO: The file is uploaded.  Now you have to insert the get_url into the database, etc.
        $.post(add_image_url,
            {
                get_url: get_url,
                price: self.vue.price
            })
    };

    self.toggle_cart = function(image_id, email) {
        $.post(toggle_cart_url,
        {
            image_id: image_id
        }, function() {

            if(self.vue.self_page == true) {
                self.get_auth_images();
            } else if(self.vue.self_page == false) {
                $.getJSON(get_images_url,
                {
                    user_email: email
                },
                function(data) {
                list = [];
                if(data.image.length == 0){
                    self.vue.user_images = list;

                    console.log(list);
                    return
                }
                for(i in data.image) {
                    list.push(data.image[i]);

                    if(list != self.vue.user_images)
                        self.vue.user_images = list;
                }
                })
            }
        })
    };

    self.set_price = function(image_index, image_price) {
        console.log("Image Index" + image_index);
        self.vue.price = image_price;
        console.log("New price" + self.vue.price);

        $.post(edit_image_price_url,
            {
                image_id: image_index,
                price: self.vue.price

            })

    };

    self.get_user_images = function(name) {
        self.vue.self_page = !self.vue.self_page
        console.log("Get user images called: " + self.vue.self_page + ": " + name);
        $.getJSON(get_user_images_url,
            {
                user_email: name.user_email
            },
            function(data){
                list = [];
                if(data.image.length == 0){
                    self.vue.user_images = list;

                    console.log(list);
                    return
                }
                for(i in data.image) {
                    list.push(data.image[i]);
                    self.vue.cart.push(data.image[i]);
                    if(list != self.vue.user_images)
                        self.vue.user_images = list;
                }
            })
            console.log("List" + list);
    };

    self.get_auth_images = function() {
        self.vue.self_page = true;
        $.getJSON(get_user_images_url,
            {
                user_email: 'hello'
            },
            function(data){
                console.log(data);
                list = [];
                if(data.image.length == 0){
                    self.vue.user_images = list;

                    return
                }
                for(i in data.image) {

                    list.push(data.image[i]);

                    self.vue.cart.push(data.image[i]);

                    if(list != self.vue.user_images)
                        self.vue.user_images = list;

                }
            })
    };


    self.get_user_names = function() {
        $.getJSON(get_user_names_url,
            function(data){
                list = [];
                for(i in data.users) {
                    list.push(data.users[i]);
                    if(list != self.vue.users)
                        self.vue.users = list;
                }

            })
    };


    self.vue = new Vue({
        el: "#vue-div",
        delimiters: ['${', '}'],
        unsafeDelimiters: ['!{', '}'],
        data: {
            is_uploading: false,
            self_page: true, // Leave it to true, so initially you are looking at your own images.
            logged_in: false,
            user_images: [],
            users: [],
            price: null,
            is_checkout: false,
            cart: []
        },
        methods: {
            open_uploader: self.open_uploader,
            close_uploader: self.close_uploader,
            upload_file: self.upload_file,
            get_user_images: self.get_user_images,
            get_user_names: self.get_user_names,
            get_auth_images: self.get_auth_images,
            set_price: self.set_price,
            checkout_pressed: self.checkout_pressed,
            toggle_cart: self.toggle_cart
        },
        created: function() {
            self.get_user_names()
        }


    });
    self.get_auth_images();

    $("#vue-div").show();


    return self;
};

var APP = null;

// This will make everything accessible from the js console;
// for instance, self.x above would be accessible as APP.x
jQuery(function(){APP = app();});

