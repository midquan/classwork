import tempfile

# Cloud-safe of uuid, so that many cloned servers do not all use the same uuids.
from gluon.utils import web2py_uuid

# Here go your api methods.

#Gets user images for all users.  
def get_user_images():
    images = []
    image_url = db().select(db.user_images.ALL)
    for i, r in enumerate(image_url):
        img = dict(
            created_on=r.created_on,
            created_by=r.created_by,
            image_url=r.image_url,
        )
        images.append(img)
    return response.json(dict(
        user_images=images,
    ))
    
#Gets user images for only the clicked specific user. 
def only_images():
    images = [] 
    email = request.vars.single_user 
    image_url = db((db.user_images.user_email == email)).select(db.user_images.ALL)
    for i, r in enumerate(image_url):
        img = dict(
            created_on=r.created_on,
            created_by=r.created_by,
            image_url=r.image_url,
        )
        images.append(img)
    return response.json(dict(
        user_images=images
    ))                
    
    
#Adds image to the overall database.  
@auth.requires_login()    
@auth.requires_signature()
def add_image():
    image_id = db.user_images.insert( image_url=request.vars.image_url,)
    im = db.user_images(image_id)
    user_images = dict(
        id=im.id,
        image_url=request.vars.image_url,
    )
    return response.json(dict(
        user_images=user_images
    ))

#Adds image to the overall database.     
def get_users():
    user_list = []
    rows = db().select(db.auth_user.ALL) 
    logged_in = auth.user_id is not None 
    for i, r in enumerate(rows):
        users = dict(
            first_name = r.first_name,
            last_name = r.last_name,
            email = r.email,
            id = r.id
        )
        user_list.append(users)        
    return response.json(dict(
        user_list=user_list,
        logged_in = logged_in
    ))