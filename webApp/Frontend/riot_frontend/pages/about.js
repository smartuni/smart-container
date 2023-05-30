import React from 'react'
import Link from 'next/link'
import styles from '../styles/about.module.css'

export default function About() {
  return (
    <div className='bg-malibu-500 h-screen'>
      <div className='bg-malibu-500 flex justify-between px-4 pt-4'>
        <h2></h2>
        <h2>Welcome back, Team!
            <span> |  
                <Link className="text-blue-500 hover:underline ml-1" href="/#">Log out</Link>
            </span>
        </h2>
      </div>
      <div className={styles.container}>
        <div className={styles.left}>
          <h2>Secure Smart Supply Chain</h2>
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
  )
}
