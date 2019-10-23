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

    //gets the google calendar of the user
    self.get_calendar = function (user_email) {
        $.post(get_user_cal_url,
            {
                single_user:user_email,},

            function (data){
                console.log("getting...: " + data);
                self.vue.calendar_url = data;
        });
    };

    self.get_user_calendar = function (user_email) {
        $.post(get_spec_user_cal_url, {
            single_user:user_email,
        },
            function (data){
                console.log("getting user...: " + data);
                self.vue.calendar_url = data;
        });
    };

    self.set_calendar = function() {
        self.vue.have_cal_url = true;
        $.post(set_cal_url,
        {
            embed_url: self.vue.calendar_url,
        },
        function (data) {
            $.web2py.enableElement($("#set_calendar_submit"))
            console.log("Calendar URL is: "+ self.vue.calendar_url);
            // self.vue.calendar_url = self.vue.calendar_url;
            console.log("Calendar embedURL is: "+ data.embed_url);
            self.vue.calendar_url = data.embed_url;
            // self.vue.calendar_url = self.vue.calendar_url;
        });
    };


    //gets user social media links 
    self.get_user_links = function (user_email) {
        console.log("in get_user_links");
        $.post(get_spec_user_link_url, {
            single_user:user_email,
        },
            function (data){
                console.log("getting user links...: " + data);

                //parsing function from https://stackoverflow.com/questions/26425637/javascript-split-string-with-white-space
                data = data.split(" ");
                var stringArray = new Array();
                for(var i =0; i < data.length; i++){
                    stringArray.push(data[i]);
                    console.log(user_email);
                    console.log("link building: "+ stringArray[i]);
                }

                self.vue.facebook_link = stringArray[0];
                self.vue.twitter_link = stringArray[1];
                self.vue.instagram_link = stringArray[2];
                self.vue.youtube_link = stringArray[3];
        });
    };

    //gets the social media links of the user
    self.get_links = function () {
        $.post(get_user_link_url,
            function (data){
                console.log("getting links...: " + data);

                //parsing function from https://stackoverflow.com/questions/26425637/javascript-split-string-with-white-space
                data = data.split(" ");
                var stringArray = new Array();
                for(var i =0; i < data.length; i++){
                    stringArray.push(data[i]);
                    console.log("link building: "+ stringArray[i]);
                }

                self.vue.facebook_link = stringArray[0];
                self.vue.twitter_link = stringArray[1];
                self.vue.instagram_link = stringArray[2];
                self.vue.youtube_link = stringArray[3];
        });
        // self.set_links();
    };

    self.set_links = function() {
        // console.log("Calendar URL is: "+ self.vue.calendar_url);
        // self.vue.have_cal_url = true;
        $.post(set_link_url,
        {
            facebook_link: self.vue.facebook_link,
            twitter_link: self.vue.twitter_link,
            instagram_link: self.vue.instagram_link,
            youtube_link: self.vue.youtube_link,
        },
        function (data) {
            $.web2py.enableElement($("#set_calendar_submit"))
            self.vue.facebook_link = data.facebook_link;
            self.vue.twitter_link = data.twitter_link;
            self.vue.instagram_link = data.instagram_link;
            self.vue.youtube_link = data.youtube_link;
            console.log("setting facebook "+ self.vue.facebook_link);
            console.log("setting witter "+ self.vue.twitter_link);
            console.log("setting instagram "+ self.vue.instagram_link);
            console.log("setting youtube "+ self.vue.youtube_link);

            });
    };    

    self.goto_calendar = function() {
        self.vue.is_home=false;
        self.vue.calendar_pressed=true;
        self.vue.social_pressed=false;
        self.vue.announcement_pressed=false;
        self.vue.gallery_pressed=false;
        self.vue.membership_pressed=false;
        self.vue.about_us_pressed=false;
        self.vue.is_adding_email=false;
    }

    self.goto_social = function() {
        self.vue.is_home=false;
        self.vue.social_pressed=true;
        self.vue.calendar_pressed=false;
        self.vue.announcement_pressed=false;
        self.vue.gallery_pressed=false;
        self.vue.membership_pressed=false;
        self.vue.about_us_pressed=false;
        self.vue.is_adding_email=false;
    }

    self.go_home = function() {
        self.vue.is_home=true;
        self.vue.calendar_pressed=false;
        self.vue.social_pressed=false;
        self.vue.announcement_pressed=false;
        self.vue.gallery_pressed=false;
        self.vue.membership_pressed=false;
        self.vue.about_us_pressed=false;
        self.vue.is_adding_email=false;
    }

    self.goto_memos = function(){
        self.vue.is_home=false;
        self.vue.calendar_pressed=false;
        self.vue.announcement_pressed=true;
        self.vue.gallery_pressed=false;
        self.vue.social_pressed=false;
        self.vue.membership_pressed=false;
        self.vue.about_us_pressed=false;
        self.vue.is_adding_email=false;
    }

    self.goto_gallery = function(user_email){
        console.log("LETS GO TO THE GALLERY");
        self.vue.is_home=false;
        self.vue.calendar_pressed=false;
        self.vue.announcement_pressed=false;
        self.vue.gallery_pressed=true;
        self.vue.social_pressed=false;
        //self.get_images(user_email);
        self.vue.membership_pressed=false;
        self.vue.about_us_pressed=false;
        self.vue.is_adding_email=false;
    }

    self.goto_membership = function() {
        self.vue.is_home=false;
        self.vue.membership_pressed=true;
        self.vue.social_pressed=false;
        self.vue.calendar_pressed=false;
        self.vue.gallery_pressed=false;
        self.vue.announcement_pressed=false;
        self.vue.about_us_pressed=false;
        self.vue.is_adding_email=false;
    };

    self.goto_about = function() {
        self.vue.is_home=false;
        self.vue.membership_pressed=false;
        self.vue.social_pressed=false;
        self.vue.calendar_pressed=false;
        self.vue.gallery_pressed=false;
        self.vue.announcement_pressed=false;
        self.vue.about_us_pressed=true;
        self.vue.is_adding_email=false;
    }

    self.get_org_info = function(user_email){
        self.vue.org_selected=true;
        self.vue.selected_user=user_email;
        self.get_images(user_email);
        self.get_user_memos(user_email);
        self.get_user_links(user_email);
        self.get_user_calendar(user_email);
        self.vue.announcement_pressed=true;
        self.vue.is_home=false;
    }

    //----------------Sanjeets Code-----------------------------------------

function get_users_url(start_idx, end_idx) {
        var pp = {
            start_idx: start_idx,
            end_idx: end_idx
        };
        return user_url + "?" + $.param(pp);
    }

    function get_user_images_url(start_idx, end_idx) {
        var pp = {
            start_idx: start_idx,
            end_idx: end_idx
        };
        return user_images_url + "?" + $.param(pp);
    }

    self.get_user_images = function () {
        $.getJSON(get_user_images_url(0, 20), function (data){
            self.vue.user_images = data.user_images;
            enumerate(self.vue.user_images);
        })
    };

    self.get_users = function (){
        $.getJSON(get_users_url(0,20), function (data){
            self.vue.user_list=data.user_list;
            enumerate(self.vue.user_list);
            }
        )
    };

    self.get_images = function(user_email) {
        $.post(images_url, {
            single_user:user_email,
        },
        function (data) {
            self.vue.user_images = data.user_images;
            enumerate(self.vue.user_images);
        });
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
        // Reads the file.
        var input = event.target;
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

    self.upload_complete = function(get_url) {
        // Hides the uploader div.
        // self.vue.show_img = true;
        self.close_uploader();
        console.log('The file was uploaded; it is now available at ' + get_url);
        // TODO: The file is uploaded.  Now you have to insert the get_url into the database, etc.
         $.post(add_image_url,
            {
                image_url: get_url
            },
            function (data) {
                console.log(data)  
                setTimeout(function() {
                    self.vue.user_images.push(data.user_images);
            //your code to be executed after 1 second
            }, 1000);
                enumerate(self.vue.user_images);
            })
        setTimeout(self.get_user_images,1000);
    };


    //Announcements default_index code

     function get_memos(start_idx, end_idx) {
        var pp = {
            start_idx: start_idx,
            end_idx: end_idx
        };
        return get_memos_url + "?" + $.param(pp);
    }

    function get_user_memos(start_idx, end_idx) {
        var pp = {
            start_idx: start_idx,
            end_idx: end_idx
        };
        return get_user_memos_url + "?" + $.param(pp);
    }

    self.get_memos = function () {
        $.getJSON(get_memos(0, 10), function (data) {
           self.vue.memos = data.memos;
           self.vue.has_more = data.has_more;
           self.vue.logged_in = data.logged_in;
           self.vue.auth_email = data.auth_email;
        })
    };

    
    self.get_user_memos = function (user_email) {
        $.post(get_user_memos_url, {
            single_user:user_email,
        }, 
        function (data) {
           self.vue.memos = data.memos;
           self.vue.has_more = data.has_more;
           self.vue.logged_in = data.logged_in;
           self.vue.auth_email = data.auth_email;
        })
    };
    

    self.get_more = function () {
        var num_memos = self.vue.memos.length;
        $.getJSON(get_memos(num_memos, num_memos + 10), function (data) {
           self.vue.has_more = data.has_more;
           self.extend(self.vue.memos, data.memos);
        })
    };

    self.add_memo_button = function () {
        self.vue.is_adding_memo = !self.vue.is_adding_memo;
    };


    self.edit_memo_button = function (memo_id) {
        for (var i = 0; i < self.vue.memos.length; i++) {
            if (self.vue.memos[i].id === memo_id) {
                self.vue.memos[i].is_being_edited = !self.vue.memos[i].is_being_edited;
            }
            else {
                self.vue.memos[i].is_being_edited = false;
            }
        }
    };

    self.add_memo = function () {
        $.post(add_memo_url,
            {
                title:self.vue.add_memo_title,
                text:self.vue.add_memo_text,
                created_on:self.vue.created_on,
            },
            function (data) {
                self.vue.memos.unshift(data.memo);
            });
        self.vue.is_adding_memo = false;
        self.vue.add_memo_title = null;
        self.vue.add_memo_text = null;
    };

    self.edit_memo = function (memo_id) {
        $.post(edit_memo_url,
            {
                memo_id:memo_id,
                title:self.vue.edit_memo_title,
                text:self.vue.edit_memo_text
            },
            function (data) {
                for (var i = 0; i < self.vue.memos.length; i++) {
                    if (self.vue.memos[i].id === memo_id) {
                        self.vue.memos[i].title = data.title;
                        self.vue.memos[i].text = data.text;
                        self.vue.memos[i].is_being_edited = false;
                    }
                }
            });
        self.vue.edit_memo_title = null,
        self.vue.edit_memo_text = null
    };

    self.delete_memo = function (memo_id) {
        $.post(del_memo_url,
            {
                memo_id:memo_id
            },
            function() {
                var idx = null;
                for (var i = 0; i < self.vue.memos.length; i++) {
                    if (self.vue.memos[i].id === memo_id){
                        idx = i + 1;
                        break;
                    }
                }
                if (idx) {
                    self.vue.memos.splice(idx - 1, 1);
                }
            }
        )
    };

    self.get_emails = function () {
        console.log("Trying to get emails");
        $.getJSON(emails_url, function (data){
            self.vue.memberships = data.memberships;
            enumerate(self.vue.memberships);
        })
    };

    self.add_email_button = function () {
        self.vue.is_adding_email = true;
    };

    self.add_email = function () {
          
        console.log("Trying to add emails");
        $.post(add_email_url,
            {
                email: self.vue.form_email,
                name: self.vue.form_name,        
                    m1: self.vue.form_m1,
                    m2: self.vue.form_m2,
                    m3: self.vue.form_m3,
                    m4: self.vue.form_m4,
                    m5: self.vue.form_m5,
                    m6: self.vue.form_m6,
                    m7: self.vue.form_m7,
                    m8: self.vue.form_m8,
                    m9: self.vue.form_m9,
                    m10: self.vue.form_m10,
                    Club: self.vue.selected_user,
            },
            function (data) {
                // $.web2py.enableElement($("#add_email_submit"));
                self.vue.is_adding_email = false;
                // self.vue.memberships.unshift(data.membership);
                self.update_emails(1);
                enumerate(self.vue.memberships);
                self.vue.form_email = "";
                self.vue.form_name = "";
                     console.log("Trying to get emails");
                     
            })
    };
     
    self.update_emails = function (extra_cls) {
        var num_cls = self.vue.memberships.length;
        $.getJSON(emails_url, function (data) {
            self.vue.memberships = data.memberships;
            enumerate(self.vue.memberships);
        });
    };

    self.cancel_add_email = function () {
        self.vue.is_adding_email = false;
    };

    self.delete_email = function(cl_idx) {
        $.post(del_email_url,
            { cl_id: self.vue.memberships[cl_idx].id },
            function () {
                self.vue.memberships.splice(cl_idx, 1);
                enumerate(self.vue.memberships)
            })
    };

    // Complete as needed.
    self.vue = new Vue({
        el: "#vue-div",
        delimiters: ['${', '}'],
        unsafeDelimiters: ['!{', '}'],
        data: {
            is_home:true,

            calendar_url: null,
            have_cal_url: false,
            calendar_pressed:false,

            facebook_link:null,
            twitter_link:null,
            instagram_link:null,
            youtube_link:null,
            social_pressed:false,

            is_adding_memo: false,
            add_memo_title: null,
            add_memo_text: null,
            created_on:null,
            edit_memo_title: null,
            edit_memo_text: null,
            has_more: false,
            logged_in: false,
            auth_email: null,
            memos: [],
            //gallery data
            is_uploading: false,
            user_images: [],
            img_url: null,
            show_img: false,
            self_page: true,
            //user data
            user_list: [],
            org_selected:false,
            selected_user:'',
            message: 'Club',
            announcement_pressed:false,
            gallery_pressed:false,

            membership_pressed:false,
            is_adding_email: false,
            memberships: [],
            form_email: null,
            form_name: null,                
            form_m1: false,
            form_m2: false,
            form_m3: false, 
            form_m4: false, 
            form_m5: false, 
            form_m6: false, 
            form_m7: false, 
            form_m8: false, 
            form_m9: false, 
            form_m10: false, 
            //about us tab
            about_us_pressed:false,
            board_member:null,
            position:null,
        },
        methods: {
            set_calendar: self.set_calendar,
            get_calendar: self.get_calendar,
            goto_calendar:self.goto_calendar,
            goto_social:self.goto_social,
            set_links: self.set_links,
            get_links:self.get_links,
            go_home:self.go_home,
            goto_memos:self.goto_memos,
            goto_gallery:self.goto_gallery,
            //anouncement methods
            get_memos: self.get_memos,
            get_more: self.get_more,
            add_memo_button: self.add_memo_button,
            edit_memo_button: self.edit_memo_button,
            add_memo: self.add_memo,
            edit_memo: self.edit_memo,
            delete_memo: self.delete_memo,
            //gallery methods
            open_uploader: self.open_uploader,
            close_uploader: self.close_uploader,
            upload_file: self.upload_file,
            get_user_images: self.get_user_images,
            get_images: self.get_images,
            //user methods
            get_users: self.get_users,
            get_org_info: self.get_org_info,

            goto_membership:self.goto_membership,
            add_email_button: self.add_email_button,
            add_email: self.add_email,
            cancel_add_email: self.cancel_add_email,
            delete_email: self.delete_email,
            goto_social:self.goto_social,
            set_links: self.set_links,
            get_links:self.get_links,
            go_home:self.go_home,

        }
    });

    self.vue.get_calendar();
    self.vue.get_links();
    self.get_emails();
    self.get_memos();
    self.get_users();
    self.get_user_images();

    $("#vue-div").show()
    return self;
};

var APP = null;

// This will make everything accessible from the js console;
// for instance, self.x above would be accessible as APP.x
jQuery(function(){APP = app();});
