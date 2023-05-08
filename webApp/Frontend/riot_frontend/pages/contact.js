import React from "react";
import Link from "next/link";
import styles from '../styles/contact.module.css'

export default function Contact() {
  return (
    <div>
        <nav>
          <ul>
            <li><a href="/">Home</a></li>
            <li><a href="#">About Us</a></li>
            <li><a href="#">Contact</a></li>
            <li><a href="#">Log out</a></li>
          </ul>
        </nav>
        <div className={styles.contact}>
        <div className={styles.section}>
            <svg viewBox="0 0 20 20" className={styles.icon}>
            <title>Email</title>
            </svg>
            <h3>Email</h3>
            <p>contact@example.com</p>
        </div>
        <div className={styles.section}>
            <svg viewBox="0 0 20 20" className={styles.icon}>
            <title>Phone</title>
            </svg>
            <h3>Phone</h3>
            <p>+1 123-456-7890</p>
        </div>
        <div className={styles.section}>
            <svg viewBox="0 0 20 20" className={styles.icon}>
            <title>Address</title>
            </svg>
            <h3>Address</h3>
            <p>123 Main St<br />Anytown, USA 12345</p>
        </div>
        </div>
    </div>
  );
}
