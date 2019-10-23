// This is the js for the default/index.html view.
// HW4: static/js/default_index.js

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

    // Show the uploader when user click to show it. Let user be able to upload images.
    self.open_uploader = function () {
        $("div#uploader_div").show();
        self.vue.is_uploading = true;
    };

    // Hides the uploader when user is done uploading.
    self.close_uploader = function () {
        $("div#uploader_div").hide();
        self.vue.is_uploading = false;
        $("input#file_input").val(""); // This clears the file choice once uploaded.

    };

    // When user choose to upload a file, the image file will be uploaded to
    // course professor's google cloud stroage.
    self.upload_file = function (event) {
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

    // Upload complete. Hides the uploader and post the image to db and website.
    self.upload_complete = function(get_url) {
        // Hides the uploader div.
        //self.vue.show_img = true;
        self.close_uploader();
        console.log('The file was uploaded; it is now available at ' + get_url);
        // TODO: The file is uploaded.  Now you have to insert the get_url into the database, etc.
        // Insert the newly added image to db
        $.post(add_image_url,
          {image_url: get_url},
          function (){}
        );
        // Retreve and display user's images
        self.get_image_list(self.vue.logged_id);
    };

    // Reterive user info
    self.get_users = function() {
        $.getJSON (get_users_url,
          function (data) {
            self.vue.users = data.users; // User in db data
            self.vue.logged_id = data.logged_id; // User's logged in ID
            self.vue.logged_in = data.logged_in; // If user is logged in or not
            self.vue.user_selected = data.logged_id; // The selected user db info.
            enumerate(self.vue.users);
          }
        );
    };

    // Helper function for get_imgae_list function below
    function image_url(id) {
        var a = {
            id:id
        };
        return get_images_url + "?" + $.param(a);
    };

    // Get the images to display that belong to specific users by passing in
    // user-specific id and display those images.
    self.get_image_list = function(id) {
        console.log('showing images belong to this user now.');
        setTimeout(function(){
            if (!self.vue.is_uploading) {
                // If id of the user has not been set yet
                if (id == -1) {
                    self.vue.user_selected = self.vue.logged_id;
                } else {
                    self.vue.user_selected = id;
                }
                $.getJSON (image_url(id),
                    function (data) {
                        self.vue.images = data.images;
                        enumerate(self.vue.images);
                    }
                );
            }
        }, 1000);
    };

    // Single function to see if things aer working.
    self.doSomething = function (id){
      console.log('I am working, my id is ' + id);
    }

    // init Vue parameters
    self.vue = new Vue({
        el: "#vue-div",
        delimiters: ['${', '}'],
        unsafeDelimiters: ['!{', '}'],
        data: {
            is_uploading: false, // Is user uploading an image right now.
            img_url: null, // Image URL for getting the image from google cloud stroage
            images: [], // Array of images for images that the webpage is going to show.
            users: [], // Array of users in db currently
            logged_in: false, // If a user is logged in or not on the webpage.
            logged_id: -1, // User ID to disdigush users from each other.
            user_selected: -1, // INdicate
            self_page: true // Leave it to true, so initially you are looking at your own images.
        },
        methods: {
            open_uploader: self.open_uploader,
            close_uploader: self.close_uploader,
            upload_file: self.upload_file,
            get_users: self.get_users,
            get_image_list: self.get_image_list,
            // doSomething: self.doSomething,
        }

    });

    self.get_users();
    self.get_image_list(self.vue.logged_id);
    $("#vue-div").show();
    return self;
};

var APP = null;

// This will make everything accessible from the js console;
// for instance, self.x above would be accessible as APP.x
jQuery(function(){APP = app();});
