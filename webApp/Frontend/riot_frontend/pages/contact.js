import React from "react";
import Link from "next/link";
import styles from '../styles/contact.module.css'
import Image from "next/image";
import img1 from '../public/contact_email_icon.png';
import img2 from '../public/contact_phone_call_icon.png';
import img3 from '../public/contact_address_icon.png';


export default function Contact() {
  return (
    <div>
        <nav>
          <ul>
            <li><a href="/">Home</a></li>
            <li><a href="/about">About Us</a></li>
            <li><a href="/map">To Map Page</a></li>
            <li><a href="#">Log out</a></li>
          </ul>
        </nav>
        <div className={styles.contact}>
          <div className={styles.section}>
            <Image src={img1} alt="Email Address Icon" className={styles.icon}/>
            <h3>Email</h3>
            <p>contact@example.com</p>
          </div>
          <div className={styles.section}>
            <Image src={img2} alt="Phone Call Icon" className={styles.icon}/>
            <h3>Phone</h3>
            <p>+49 40 42875-8452</p>
          </div>
          <div className={styles.section}>
            <Image src={img3} alt="Address Icon" className={styles.icon}/>
            <h3>Address</h3>
            <p>HAW Hamburg<br />Berliner Tor 7<br />D-20099 Hamburg, Germany</p>
          </div>
        </div>
    </div>
  );
}
