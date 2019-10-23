import tempfile

# Cloud-safe of uuid, so that many cloned servers do not all use the same uuids.
import json
from gluon.utils import web2py_uuid
# Here go your api methods.


# let default index know if there is a user logged in
#   and if there is what the email is
def user_info():
    logged_in = auth.user is not None
    logged_in_user_email = None

    if logged_in:
        logged_in_user_email = auth.user.email
        # check of user has images
        image_count = db(db.user_images.user_email == auth.user.email).count()
        # if 0, will be false and user has no images
        user_has_image = image_count > 0
    else:
        user_has_image = 0

    return response.json(dict(
        logged_in=logged_in,
        logged_in_user_email=logged_in_user_email,
        user_has_image=user_has_image
    ))


def set_user_list():

    user_list = []

    logged_in_user_email = None
    if auth.user is not None:  # logged in
        logged_in_user_email = auth.user.email

    # get unique user emails from all those who have uploaded an image
    rows = db().select(
        db.user_images.user_email,
        db.user_images.user_first_name,
        db.user_images.user_last_name,
        distinct=True)

    for row in rows:
        u = dict(
            user_email=row.user_email,
            user_first_name=row.user_first_name,
            user_last_name=row.user_last_name
        )

        if row.user_email == logged_in_user_email:
            user_list.insert(0, u)  # if the user is logged in, put their name at the top
        else:
            user_list.append(u)

    return response.json(dict(
        user_list=user_list
    ))


@auth.requires_signature()
def add_image():
    iID = db.user_images.insert(
        image_url=request.vars.get_url,
        price=request.vars.price
    )

    return response.json(dict(
        iID=iID,
        image_url=request.vars.get_url
    ))


# @auth.requires_signature()
def get_images():
    # get the images of the selected user
    rows = db(db.user_images.user_email == request.vars.selected_email).select(orderby=~db.user_images.created_on)
    # get the images for the user with the selected email in decending order by upload time

    user_image_urls = []

    for row in rows:
        i = dict(
            id=row.id,
            user_email=row.user_email,
            user_first_name=row.user_first_name,
            user_last_name=row.user_last_name,
            image_url=row.image_url,
            created_on=row.created_on,
            price=row.price,
            being_edited=row.being_edited,
        )
        user_image_urls.append(i)

    return response.json(dict(
        user_image_urls=user_image_urls
    ))


def edit_image_price():
    image_Obj = db(db.user_images.id == request.vars.image_ID).select().first()
    status = image_Obj.being_edited

    image_Obj.update_record(being_edited=not status)

    return response.json(dict(
        new_status=not status
    ))


def set_image_price():
    image_Obj = db(db.user_images.id == request.vars.image_ID).select().first()
    status = image_Obj.being_edited

    image_Obj.update_record(being_edited=not status)  # set that it is no longer being edited
    image_Obj.update_record(price=request.vars.new_price)  # set new price

    return response.json(dict(
        new_status=not status
    ))


def image_url_to_cart():
    url = None
    image_Obj = db(db.user_images.id == request.vars.image_ID).select().first()

    return response.json(dict(
        image_info=dict(
            id=image_Obj.id,
            user_first_name=image_Obj.user_first_name,
            user_last_name=image_Obj.user_last_name,
            image_url=image_Obj.image_url,
            created_on=image_Obj.created_on,
            price=image_Obj.price,
        ),
        new_total=float(request.vars.total_sum_so_far) + float(image_Obj.price)
    ))


def purchase():
    """Ajax function called when a customer orders and pays for the cart."""
    if not URL.verify(request, hmac_key=session.hmac_key):
        raise HTTP(500)
    # Creates the charge.
    import stripe
    # Your secret key.
    stripe.api_key = myconf.get('stripe.private_key')
    token = json.loads(request.vars.transaction_token)
    amount = float(request.vars.amount)
    try:
        charge = stripe.Charge.create(
            amount=int(amount * 100),
            currency="usd",
            source=token['id'],
            description="Purchase",
        )
    except stripe.error.CardError as e:
        logger.info("The card has been declined.")
        logger.info("%r" % traceback.format_exc())
        return "nok"

    return "ok"
