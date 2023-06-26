"use client";
import Button from "../components/Button";
import TextBox from "../components/TextBox";
import React, { useRef } from "react";
import styles from '../styles/Signin.module.css'

const SignUp_page = () => {
  const userName = useRef("");
  const pass = useRef("");
  const firstName = useRef("");
  const lastName = useRef("");

  const onSubmit = async () => {
    console.log("Sign Up Pressed!");
    const res = await fetch("http://178.128.192.215:8000/api/signUp/", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ 
        email: userName.current, //username entered by the user in textbox
        password: pass.current,
        firstName: firstName.current,
        lastName: lastName.current,
        company: "HAW",
      }), 
    });
    console.log("Email: " + userName.current + " pass: " + pass.current + " fName: " + firstName.current + " lName: " + lastName.current);
    if (res.ok) {
      console.log("New user added.");
      window.location.href = "/dashboard";
    } else {
      console.log("Response not OK!");
    }
  }; 

  return (
    <div className={"flex flex-col justify-center items-center h-screen bg-malibu-500"}> 
      <h1 className={styles.signin_header}>Sign up</h1>
      <div className={styles.signinNew}>
        <TextBox className={styles['form-group']}
          lableText="First Name" placeholder="first name"
          onChange={(e) => (firstName.current = e.target.value)}
        />
        <TextBox className={styles['form-group']}
          lableText="Last Name" placeholder="last name"
          onChange={(e) => (lastName.current = e.target.value)}
        />
        <TextBox className={styles['form-group']} 
          lableText="Email" placeholder="email" 
          onChange={(e) => (userName.current = e.target.value)} 
        />
        <TextBox className={styles['form-group']}
          lableText="Password" placeholder="password"
          type={"password"}
          onChange={(e) => (pass.current = e.target.value)}
        />
        <Button onClick={onSubmit}>Sign Up</Button>
        <footer>
            <p>If you already have an account, please<br/> <a href="/signin_page">log in here</a>.</p>
        </footer>
      </div>
    </div>
  );
};

export default SignUp_page;
