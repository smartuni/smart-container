import NextAuth from "next-auth";
import CredentialsProvider from "next-auth/providers/credentials";

export default NextAuth({
  providers: [
    CredentialsProvider({
      name: "Credentials",
      credentials: {
        username: { label: "Username", type: "text", placeholder: "email" },
        password: { label: "Password", type: "password" },
      },
      async authorize(credentials, req) {
        // Handle the case when 'credentials' is undefined
        /* if (!credentials) {
          throw new Error("Invalid credentials");
        } */
        // Mock user lookup logic for testing
        /* const mockUser = {
          id: 1,
          name: "John Smith",
          email: "john@example.com",
        };
        // Simulate a delay to mimic an asynchronous operation
        await new Promise((resolve) => setTimeout(resolve, 1000));
        if (
          credentials.username === "john@example.com" &&
          credentials.password === "123"
        ) {
          return mockUser;
        } else {
          throw new Error("Invalid credentials");
        } */

        extract_user = response => {

          let response_body_obj = JSON.parse(response.payload); // Turn the response body JSON into an object
      
          let access_jwt_str = response_body_obj?.access; // Get the access token (JWT) from body object
      
          let jwt_payload_base64 = access_jwt_str?.split('.')[1]; // Split the jwt at every '.' and use first index to get Base64 encoded payload (JWT => header.payload.signature => 0.1.2)
      
          let jwt_payload = atob(jwt_payload_base64); // Decode the Base64 encoded payload
      
          let user = JSON.parse(jwt_payload); // Turn the decoded payload JSON string into the an object
      
          return user;
      
        }
        
        const res = await fetch("http://178.128.192.215:8000/api/signIn", {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({ //constructs the request body
            email: credentials?.username, //data to be sent in the request body
            password: credentials?.password, //data to be sent in the request body
          }),
        });
        const user = await res.json();

        if (user) {
          return user;
        } else {
          return null;
        }
      },
    }),
  ],

  pages: {
    signIn: "/signin_page",
  },
});
