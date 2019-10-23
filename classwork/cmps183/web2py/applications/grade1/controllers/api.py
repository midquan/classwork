import tempfile

# Cloud-safe of uuid, so that many cloned servers do not all use the same uuids.
from gluon.utils import web2py_uuid

# Here go your api methods.

@auth.requires_signature()
def toggle_cart():
    img = db(db.image_list.id == request.vars.img_id).select().first()
    img.update_record(in_cart=not img.in_cart)

@auth.requires_signature()
def update_price():
    img = db(db.image_list.id == request.vars.img_id).select().first()
    img.update_record(price=request.vars.price)

@auth.requires_signature()
def add_image():
    print "Hello"
    # Inserts the image
    img_id = db.image_list.insert(image_url = request.vars.image_url, price = request.vars.price)
    return response.json(dict(image_list=dict(
        image_url = request.vars.image_url,
        price = request.vars.price
    )))

@auth.requires_signature(hash_vars=False)
def get_images():
    start_idx = int(request.vars.start_idx) if request.vars.start_idx is not None else 0
    end_idx = int(request.vars.end_idx) if request.vars.end_idx is not None else 0
    image_list = []
    rows = db(db.image_list.user_email == request.vars.email).select(db.image_list.ALL, limitby=(start_idx, end_idx + 1))
    for i, r in enumerate(rows):
        if i < end_idx - start_idx:
            img = dict(
                id = r.id,
                user_email = r.user_email,
                image_url = r.image_url,
                in_cart = r.in_cart,
                price = r.price
            )
            image_list.append(img)
    logged_in = auth.user is not None
    return response.json(dict(image_list=image_list, logged_in=logged_in))

@auth.requires_signature(hash_vars=False)
def get_user_list():
    print "HERRO WORLD"
    user_list = []
    for r in db(db.auth_user.id != auth.user.id).select():
       dat = dict(
            name = (r.first_name + " " + r.last_name),
            email = r.email
       )
       user_list.append(dat)
    return response.json(dict(user_list=user_list))

@auth.requires_signature(hash_vars=False)
def get_user():
    print "HERRO WORLD"
    user_list2 = []
    r = db(db.auth_user.email == auth.user.email).select().first()
    user = dict(
        name = (r.first_name + " " + r.last_name),
        email = r.email
    )
    user_list2.append(user)
    return response.json(dict(user_list2=user_list2))
