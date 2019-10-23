import tempfile

# Cloud-safe of uuid, so that many cloned servers do not all use the same uuids.
from gluon.utils import web2py_uuid

# Here go your api methods.
def edit_image_price():
    image_id = db(db.images.id == request.vars.image_id).select().first()
    image_id.update_record(price=request.vars.price)
    print(image_id)

def add_image():
    print("hereee");
    image_id = db.images.insert(url=request.vars.get_url, price=request.vars.price)
    return

def get_user_images():
    # need to use request.vars.user_id to get the images
    email_request = request.vars.user_email
    if email_request == 'hello':
        email_request = auth.user.email
    user_images = db(db.images.user_email == email_request).select()
    urls = []

    # go through user images and extract data
    for image in user_images:
        list = dict(
            id=image.id,
            user_email=image.user_email,
            user_id=image.user_id,
            url=image.url,
            price=image.price,
            updated_on=image.updated_on,
            is_in_cart=image.is_in_cart
        )
        urls.append(list)
        print(urls);

    return response.json(dict(image=urls))

def get_images():
    email_received = request.vars.user_email
    user_images = db(db.images.user_email == email_received).select()
    urls = []
    # go through user images and extract data
    for image in user_images:
        list = dict(
            id=image.id,
            user_email=image.user_email,
            user_id=image.user_id,
            url=image.url,
            price=image.price,
            updated_on=image.updated_on,
            is_in_cart=image.is_in_cart
        )
        urls.append(list)
        print(urls);

    return response.json(dict(image=urls))

def get_user_names():
    if auth.user is not None:
        user_table = db(db.auth_user.id != auth.user.id).select()
    else:
        user_table = db(db.auth_user.id).select()

    users = []

    # go through user images and extract data
    for name in user_table:
        list = dict(
            user_name=name.first_name,
            user_email=name.email
        )
        users.append(list)

    return response.json(dict(users=users))

def toggle_cart():
    row = db(db.images.id == request.vars.image_id).select().first()
    row.update_record(is_in_cart = not row.is_in_cart)
    print(row)
