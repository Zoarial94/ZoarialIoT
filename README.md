# ZoarialIoT
A project for learning about networking, configuration files, MySQL databases, and security.

Originally, i didnt realize how much of a security concern this was, but i think it is a good challange to think about and learn from.


Most of the security will have to be handled by the user.
The biggest security feature will be implemented in 'rings.' Each command will have to specify the minimum ring in order for it to be a valid request.
This is just some first thoughs and will change.

Ring 1 will be unsecured. It will be a plain-text request and really only meant for lights or devices like arduinos.

Ring 2 will be slightly better. Plain-text with [HOTP](https://en.wikipedia.org/wiki/HMAC-based_One-time_Password_Algorithm) or [TOTP](https://en.wikipedia.org/wiki/Time-based_One-time_Password_Algorithm). Basically ring 1 with a 6-digit code that changes for each request.

Ring 3 will have an encrypted communication between the two.

Ring 4 will have encrypted communication WITH identiy verification using (probably) public keys. Very much like an ssh connection.
