# Define your tables below (or better in another model file) for example
#
# >>> db.define_table('mytable', Field('myfield', 'string'))
#
# Fields can be 'string','text','password','integer','double','boolean'
#       'date','time','datetime','blob','upload', 'reference TABLENAME'
# There is an implicit 'id integer autoincrement' field
# Consult manual for more options, validators, etc.

import datetime

def get_user_email():
    return auth.user.email if auth.user is not None else None


db.define_table('calendar',
                Field('user_email', default=get_user_email()),
                Field('embed_url'),
                )

db.define_table('social_media',
				Field('user_email', default=get_user_email()),
				Field('facebook_link'),
				Field('twitter_link'),
				Field('instagram_link'),
				Field('youtube_link'),
				)


db.define_table('checklist',
                Field('user_email', default=get_user_email()),
                Field('is_public', 'boolean', default=True),
                Field('title'),
                Field('memo', 'text'),
                Field('created_on', 'datetime', update=datetime.datetime.utcnow())
                )

db.define_table('user_images',
              	Field('user_email', default=get_user_email()),
                Field('created_on', 'datetime', default=request.now),
                Field('created_by', 'reference auth_user', default=auth.user_id),
                Field('image_url')
                )

db.define_table('membership',
                Field('email'),
                Field('Club', default=True),
                Field('name', 'text'),
                Field('m1', 'boolean'),
                Field('m2', 'boolean'),
                Field('m3', 'boolean'),
                Field('m4', 'boolean'),
                Field('m5', 'boolean'),
                Field('m6', 'boolean'),
                Field('m7', 'boolean'),
                Field('m8', 'boolean'),
                Field('m9', 'boolean'),
                Field('m10', 'boolean'),
                Field('core', 'boolean', default=False),
                Field('updated_on', 'datetime', default=datetime.datetime.utcnow())                  
                )

db.define_table('about_us_images',
                Field('user_email', default=get_user_email()),
                Field('created_on', 'datetime', default=request.now),
                Field('created_by', 'reference auth_user', default=auth.user_id),
                Field('image_url'),
                Field('board_member', 'text'),
                Field('position_name', 'text')
                )

# after defining tables, uncomment below to enable auditing
# auth.enable_record_versioning(db)
