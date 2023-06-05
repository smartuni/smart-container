import NextAuth from "next-auth";
import CredentialsProvider from "next-auth/providers/credentials";

export default NextAuth({
  providers: [
    CredentialsProvider({
      name: "Credentials",
      credentials: {
        username: { label: "Username", type: "text", placeholder: "jsmith" },
        password: { label: "Password", type: "password" },
      },
      async authorize(credentials, req) {
        // Handle the case when 'credentials' is undefined
        if (!credentials) {
          throw new Error("Invalid credentials");
        }
        // Mock user lookup logic for testing
        const mockUser = {
          id: 1,
          name: "John Smith",
          email: "john@example.com",
        };
        // Simulate a delay to mimic an asynchronous operation
        await new Promise((resolve) => setTimeout(resolve, 1000));
        if (
          credentials.username === "jsmith" &&
          credentials.password === "password123"
        ) {
          return mockUser;
        } else {
          throw new Error("Invalid credentials");
        }

        const res = await fetch("http://127.0.0.1:8000/api/signIn", {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({
            username: credentials?.username,
            password: credentials?.password,
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
