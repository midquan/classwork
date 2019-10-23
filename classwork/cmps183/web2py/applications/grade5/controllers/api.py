# HW4: controllers/api.py

import tempfile

# Cloud-safe of uuid, so that many cloned servers do not all use the same uuids.
from gluon.utils import web2py_uuid

# Here go your api methods.

# Add images to db named image_list and return image id
@auth.requires_signature()
def add_image():
    imageid = db.image_list.insert(
        image_url = request.vars.image_url
    )
    return response.json(dict(memo=dict(
        id = imageid
    )))


# Print out all the images a user uploaded and owns.
# @auth.requires_signature()
def get_image_list():
    id = request.vars.id
    images = []
    # u = auth.user_id
    if int(id) == -1:
        if auth.user_id is not None:
            rows = db(db.image_list.created_by == auth.user_id).select(orderby=~db.image_list.created_on)
    else:
        rows = db(db.image_list.created_by == request.vars.id).select(orderby=~db.image_list.created_on)

    for i, r in enumerate(rows):
        #print "****\n",r,"\n*****"
        d = dict (
            image_url = r.image_url
        )
        images.append(d)
    return response.json(dict(
        images=images
    ))
    # u = db(db.auth_user.email == email)
    # print u


# Retrive data of all users for right side user table.
@auth.requires_signature()
def get_users():
    # print "get users:"
    users = []
    current_user = None
    rows =  db(db.auth_user).select()
    logged_in = auth.user_id is not None

    for i, r in enumerate(rows):
        # If user is logged in AND the id of current user is the same as r.id,
        # then set variables to current user.
        if logged_in and r.id == auth.user_id:
            current_user = dict (
                id = r.id,
                firstName = r.first_name,
                lastName = r.last_name
            )
        # If not, set variables
        else:
            t = dict(
                id = r.id,
                firstName = r.first_name,
                lastName = r.last_name
            )
            # Append the data into users array.
            users.append(t)

    if logged_in:
        users.insert(0, current_user)

    # Returning user info.
    return response.json( dict(
        users = users,
        logged_id = auth.user_id,
        logged_in = logged_in
    ))
