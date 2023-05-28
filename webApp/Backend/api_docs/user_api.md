# User API

Using the User API, one can access the user data stored in the database. All user data is constructed with five columns per table entry. These are

- first_name: The first name of the user as String.
- last_name: The last name of the user as String.
- email: The email of the user as String.
- password: The password of the user as String.
- id: A UUID that distinquishes the user data entry from the rest (primary key).
- company: The company the user belongs to as String.
- role: The role of the user as String.

A user data entry returns their contents based on the provided API endpoint in JSON format.

## UserList

> List all user data, or create a new user data list

This view can be accessed using this statement:

```js
const userListResponse = await fetch("http://127.0.0.1:8000/user_list");
```