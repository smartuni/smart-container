"use client";
import Button from "../components/Button";
import TextBox from "../components/TextBox";
//import { signIn } from "next-auth/react";
import React, { useRef } from "react";
import styles from '../styles/Signin.module.css'

const LoginPage = () => {
  const userName = useRef("");
  const pass = useRef("");

  /* const onSubmit = async () => {
    const result = await signIn("credentials", {
      email: userName.current,
      password: pass.current,
      redirect: true,
      callbackUrl: "/dashboard",
    });
  }; */

  const onSubmit = async () => {
    console.log("Login Pressed!");
    const res = await fetch("http://178.128.192.215:80/api/signIn/", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ 
        email: userName.current, //username entered by the user in textbox
        password: pass.current, //password entered by the user in textbox
      }), //"email": "sahar.behravesh@gmail.com", password: "Sahar1364"
    });
    console.log("Email: " + userName.current);
    const response_body = await res.json(); // Parse the response body as JSON
    if (res.ok) {
      const user = extract_user(response_body); // Call the extract_user function with the response body 
      localStorage.setItem('localuser', JSON.stringify(user));
      console.log(localStorage);
      console.log(user);
      window.location.href = "/dashboard";
      return user;
    } else {
      console.log("Response not OK!");
      return null;
    }
  }; 

  const extract_user = (response) => {
    let access_jwt_str = response?.access;
    let jwt_payload_base64 = access_jwt_str?.split('.')[1];
    let jwt_payload = Buffer.from(jwt_payload_base64, 'base64'); //equivalent to atob
    let user = JSON.parse(jwt_payload);
    return user;
  };

  return (
    <div className={"flex flex-col justify-center items-center h-screen bg-malibu-500"}> 
      <h1 className={styles.signin_header}>Sign in</h1>
      <div className={styles.signinNew}>
        <TextBox className={styles['form-group']} lableText="Email" placeholder="Email" onChange={(e) => (userName.current = e.target.value)} />
        <TextBox className={styles['form-group']}
          lableText="Password" placeholder="Password"
          type={"password"}
          onChange={(e) => (pass.current = e.target.value)}
        />
        <Button onClick={onSubmit}>Login</Button>
        <footer>
                <p>If you don't have an account, please <a href="/signup">sign up here</a>.</p>
              </footer>
      </div>
    </div>
  );
};

export default LoginPage;
