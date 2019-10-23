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
    return auth.user.email if auth.user else None


def get_user_name(subname):
    name = None
    if subname == "first":
        name = auth.user.first_name if auth.user else None
    elif subname == "last":
        name = auth.user.last_name if auth.user else None

    return name

# after defining tables, uncomment below to enable auditing
# auth.enable_record_versioning(db)


db.define_table('user_images',
                Field('user_email', default=get_user_email()),
                Field('user_first_name', default=get_user_name("first")),
                Field('user_last_name', default=get_user_name("last")),
                Field('created_by', 'reference auth_user', default=auth.user_id),
                Field('created_on', 'datetime', default=request.now),
                Field('image_url'),
                Field('price', 'float'),
                Field('being_edited', 'boolean', default=False),
                )

from gluon.utils import web2py_uuid
if session.hmac_key is None:
    session.hmac_key = web2py_uuid()

db.user_images.created_by.writable = False
db.user_images.created_by.readable = False
db.user_images.created_on.writable = db.user_images.created_on.readable = False
db.user_images.id.writable = db.user_images.id.readable = False
db.user_images.image_url.readable = db.user_images.image_url.writable = False
