# Here go your api methods.

import tempfile

# Cloud-safe of uuid, so that many cloned servers do not all use the same uuids.
from gluon.utils import web2py_uuid

@auth.requires_signature()
def set_cal():
	url = db.calendar.insert(
		embed_url = request.vars.embed_url,)
	u = db.calendar(url)
	row = ((db.calendar.user_email == auth.user.email))
	row2 = db(row).select().first()
	row2.update_record(
		embed_url = request.vars.embed_url,)
	calendar = dict(
		id = u.id,
		embed_url = request.vars.embed_url,)
	return response.json(dict(calendar=calendar,))
	# return u.embed_url

# @auth.requires_login()
def get_user_cal():
	# user=request.vars.single_user

	if auth.user is not None:
		rows = db((db.calendar.user_email == auth.user.email)).select().first()
		# rows = db((db.calendar.user_email == auth.user.email)).select(db.calendar.ALL)
	else:
		rows = db((db.calendar.user_email)).select().first()
		# rows = db((db.calendar.user_email == user)).select(db.calendar.ALL)#.first()
		embed = rows.embed_url
	logger.info(embed)
	return embed

# @auth.requires_login()
def get_spec_user_cal():
    user = request.vars.single_user
    if auth.user is not None:
        rows = db((db.calendar.user_email == auth.user.email)).select().first()
        # rows = db((db.calendar.user_email == auth.user.email)).select(db.calendar.ALL)
    else:
        rows = db((db.calendar.user_email == user)).select(db.calendar.ALL)
    for i, r in enumerate(rows):
        embed = r.embed_url
    
    logger.info(embed)
    return embed

@auth.requires_signature()
def set_link():
	url = db.social_media.insert(
		facebook_link = request.vars.facebook_link,
		twitter_link = request.vars.twitter_link,
		instagram_link = request.vars.instagram_link,
		youtube_link = request.vars.youtube_link,
		)
	u = db.social_media(url)
	row = ((db.social_media.user_email == auth.user.email))
	row2 = db(row).select().first()
	row2.update_record(
		facebook_link = request.vars.facebook_link,
		twitter_link = request.vars.twitter_link,
		instagram_link = request.vars.instagram_link,
		youtube_link = request.vars.youtube_link,)
	social_media=dict(
		id=u.id,
		facebook_link = request.vars.facebook_link,
		twitter_link = request.vars.twitter_link,
		instagram_link = request.vars.instagram_link,
		youtube_link = request.vars.youtube_link,
		)
	return response.json(dict(social_media=social_media,))

# @auth.requires_login()
def get_spec_user_link():
    logger.info("we here")
    links=[]
    user = request.vars.single_user
    #rows = db((db.social_media.user_email == user)).select(db.social_media.ALL) 
    if auth.user is not None:
        rows = db((db.social_media.user_email == auth.user.email)).select().first()
    else:
        rows = db((db.social_media.user_email == user)).select(db.social_media.ALL)

    for i, r in enumerate(rows):
        facebook = r.facebook_link
        instagram = r.instagram_link
        youtube = r.youtube_link
        twitter = r.twitter_link

    logger.info("facebook.api " + facebook)
    logger.info("twitter.api " + twitter)
    logger.info("instagram.api " + instagram)
    logger.info("youtube.api " + youtube)
    return facebook + " " + twitter + " " + instagram + " " + youtube


# @auth.requires_login()
def get_user_link():
	links=[]
	if auth.user is not None:
		rows = db((db.social_media.user_email == auth.user.email)).select().first()
	else:
		rows = db((db.social_media.user_email)).select().first()

	facebook = rows.facebook_link
	instagram = rows.instagram_link
	youtube = rows.youtube_link
	twitter = rows.twitter_link

	logger.info("facebook.api " + facebook)
	logger.info("twitter.api " + twitter)
	logger.info("instagram.api " + instagram)
	logger.info("youtube.api " + youtube)
	return facebook + " " + twitter + " " + instagram + " " + youtube



# -------------------------------------------------------------------------------


# Method add_image is used during upload to store the image URL (you have it in variable get_url)
@auth.requires_login()
@auth.requires_signature()
def add_image():
    image_id = db.user_images.insert(
        image_url = request.vars.image_url,
    )
    im = db.user_images(image_id)
    user_images = dict(
        id=image_id,
        image_url=request.vars.image_url,
        user_email=request.vars.user_email,
    )
    return response.json(dict(user_images=user_images
    ))

# Method get_user_images is used to return the list of images for everyone
def get_user_images():
    start_idx = int(request.vars.start_idx) if request.vars.start_idx is not None else 0
    end_idx = int(request.vars.end_idx) if request.vars.end_idx is not None else 0
    user_images = []
    # rows = db().select(db.user_images.ALL) 
    if auth.user is not None:
        rows = db((db.user_images.user_email == auth.user.email)).select(db.user_images.ALL)
    else:
        rows = db((db.user_images.user_email)).select().first()
    for i, r in enumerate(rows):
        if i < end_idx - start_idx:
            img = dict(
                id = r.id,
                user_email=r.user_email,
                created_on = r.created_on,
                created_by = r.created_by,
                image_url = r.image_url
            )
            user_images.append(img)
    return response.json(dict(
        user_images=user_images,
    ))

#@auth.requires_login()
def get_users():
    user_list = [] 
    for r in db(db.auth_user.id > 0).select():
        j = dict(
        first_name = r.first_name,
        last_name = r.last_name,
        email = r.email,
        )
        user_list.append(j)
    return response.json(dict(
        user_list=user_list,
    ))

# Method get_images is used to return the list of images for a specific user(ORG LIST)
def get_images():
    user_images = []
    user = request.vars.single_user
    rows = db((db.user_images.user_email == user)).select(db.user_images.ALL) 
    for i, r in enumerate(rows):
            img = dict(
                id = r.id,
                user_email=r.user_email,
                created_on = r.created_on,
                created_by = r.created_by,
                image_url = r.image_url
            )
            user_images.append(img)
    return response.json(dict(
        user_images=user_images,
    ))

### Announcements API methods: ###
def get_memos():
    memos = []
    has_more = False
    rows = None
    start_idx = int(request.vars.start_idx) if request.vars.start_idx is not None else 0
    end_idx = int(request.vars.end_idx) if request.vars.end_idx is not None else 0

    if auth.user is None:
        rows = db(db.checklist.is_public == True).select(limitby=(start_idx, end_idx + 1))
    else:
        rows = db((db.checklist.user_email == auth.user.email) |
                  (db.checklist.is_public == True)).select(limitby=(start_idx, end_idx + 1))
    for i, r in enumerate(rows):
        if i < 10:
            m = dict(
                id=r.id,
                title=r.title,
                text=r.memo,
                created_on=r.created_on,
                is_public=r.is_public,
                user_email=r.user_email,
                is_being_edited=False,
            )
            memos.append(m)
        else:
            has_more = True
            break
    logged_in = auth.user_id is not None
    auth_email = None
    if logged_in:
        auth_email = auth.user.email
    return response.json(dict(
        memos=memos,
        has_more=has_more,
        logged_in=logged_in,
        auth_email=auth_email
    ))

# gets an organizations specific announcments; takes in user email and compares
def get_user_memos():
    memos = []
    has_more = False
    rows = None
    # start_idx = int(request.vars.start_idx) if request.vars.start_idx is not None else 0
    # end_idx = int(request.vars.end_idx) if request.vars.end_idx is not None else 0

    user = request.vars.single_user
    #if auth.user is None:
    #    rows = db(db.checklist.is_public == True).select(limitby=(start_idx, end_idx + 1))
    #else:
    #    rows = db((db.checklist.user_email == auth.user.email) |
    #              (db.checklist.is_public == True)).select(limitby=(start_idx, end_idx + 1))
    rows = db((db.checklist.user_email == user)).select(db.checklist.ALL)
    for i, r in enumerate(rows):
        #if i < 10:
            m = dict(
                id=r.id,
                title=r.title,
                text=r.memo,
                created_on=r.created_on,
                is_public=r.is_public,
                user_email=r.user_email,
                is_being_edited=False,
            )
            memos.append(m)
    logged_in = auth.user_id is not None
    auth_email = None
    if logged_in:
        auth_email = auth.user.email
    return response.json(dict(
        memos=memos,
        has_more=has_more,
        logged_in=logged_in,
        auth_email=auth_email
    ))


@auth.requires_signature()
def add_memo():
    memo_id = db.checklist.insert(
        title=request.vars.title,
        memo=request.vars.text
    )
    r = db.checklist(memo_id)
    memo = dict(
        id=r.id,
        title=r.title,
        text=r.memo,
        created_on=r.created_on,
        is_public=r.is_public,
        user_email=r.user_email,
        is_being_edited=False,
    )
    return response.json(dict(memo=memo))

@auth.requires_signature()
def edit_memo():
    memo_id = request.vars.memo_id
    title = request.vars.title
    memo = request.vars.text

    q = db((db.checklist.user_email == auth.user.email) &
           (db.checklist.id == memo_id))
    entry = q.select().first()
    entry.update_record(title=title, memo=memo)

    return response.json(dict(title=title, text=memo))


@auth.requires_signature()
def delete_memo():
    memo_id = request.vars.memo_id
    q = db((db.checklist.user_email == auth.user.email) &
           (db.checklist.id == memo_id))
    q.delete()

    return 200

#-------------------------------------------------------------------------------
def get_emails():
    """This controller gets the posts."""

    get_core()


    memberships = []
    email = auth.user.email
    print email 
    rows = db((db.membership.Club == email)).select(db.membership.ALL)
    for i, r in enumerate(rows):
            cl = dict(
                 id = r.id,
                 email = r.email,
                 name = r.name,
             m1 = r.m1,
             m2 = r.m2,
             m3 = r.m3,
             m4 = r.m4,
             m5 = r.m5,
             m6 = r.m6,
             m7 = r.m7,
             m8 = r.m8,
             m9 = r.m9,
             m10 = r.m10,
             Club = r.Club,
             core = r.core,
             updated_on=r.updated_on
            )
            memberships.append(cl)
    return response.json(dict(
        memberships=memberships
    ))
     
def add_email():
   cl_id = db.membership.insert(
      email = request.vars.email,
      name = request.vars.name,
      m1 = request.vars.m1,
      m2 = request.vars.m2,
      m3 = request.vars.m3,
      m4 = request.vars.m4,
      m5 = request.vars.m5,
      m6 = request.vars.m6,
      m7 = request.vars.m7,
      m8 = request.vars.m8,
      m9 = request.vars.m9,
      m10 = request.vars.m10,
      Club = request.vars.Club,
      updated_on=request.vars.updated_on
   )
   return response.json(dict(track=dict(
         id = cl_id,
         email = request.vars.email,
         name = request.vars.name,
         m1 = request.vars.m1,
         m2 = request.vars.m2,
         m3 = request.vars.m3,
         m4 = request.vars.m4,
         m5 = request.vars.m5,
         m6 = request.vars.m6,
         m7 = request.vars.m7,
         m8 = request.vars.m8,
         m9 = request.vars.m9,
         m10 = request.vars.m10,
         updated_on=request.vars.updated_on
   )))
   
def del_name():
    """Used to delete a post."""
    db(db.membership.id == request.vars.cl_id).delete()
    return "ok"

def get_core():
    """Sees if user is core"""
    db((db.membership.m1 == True) 
    & (db.membership.m2 == True)
    & (db.membership.m3 == True)).update(core = True)

    db((db.membership.m2 == True) 
    & (db.membership.m3 == True)
    & (db.membership.m4 == True)).update(core = True)
 
    db((db.membership.m3 == True) 
    & (db.membership.m4 == True)
    & (db.membership.m5 == True)).update(core = True)

    db((db.membership.m4 == True) 
    & (db.membership.m5 == True)
    & (db.membership.m6 == True)).update(core = True)

    db((db.membership.m5 == True) 
    & (db.membership.m6 == True)
    & (db.membership.m7 == True)).update(core = True)

    db((db.membership.m6 == True) 
    & (db.membership.m7 == True)
    & (db.membership.m8 == True)).update(core = True)

    db((db.membership.m7 == True) 
    & (db.membership.m8 == True)
    & (db.membership.m9 == True)).update(core = True)

    db((db.membership.m8 == True) 
    & (db.membership.m9 == True)
    & (db.membership.m10 == True)).update(core = True)









