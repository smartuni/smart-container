import React from 'react'
import Link from 'next/link'
import styles from '../styles/about.module.css'

export default function About() {
  return (
    <>
    <div className='bg-malibu-500 min-h-screen'>
      <nav>
          <ul>
            <li><a href="/">Home</a></li>
            <li><a href="/contact">Contact</a></li>
            <li><a href="/map">To Map Page</a></li>
            <li><a href="#">Log out</a></li>
          </ul>
        </nav>
        <div className={styles.container}>
          <div className={styles.left}>
            <h2 className=''>Secure Smart Supply Chain</h2>
            <h3>We build <u>smart containers</u> that:</h3>
            <ul>
              <li>Increase transparency and security.</li>
              <li>Provide real-time information about the cargo.</li>
              <li>Use standardized IoT technologies to ensure reliability and interoperability among containers.</li>
            </ul>
          </div>
          <div className={styles.right}>
            <img src="/supply_chain.png" alt="Image" />
          </div>
      </div>
    </div>
      
    </>
  )
}
