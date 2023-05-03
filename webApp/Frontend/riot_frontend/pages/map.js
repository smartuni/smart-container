import React from "react";
import Link from "next/link";
import styles from '../styles/map.module.css'
import Image from "next/image";
import img from "/public/Map2.png";

export default function Map() {
  return (
    <div>
      <div>
        <nav >
          <ul>
            <li><a href="/">Home</a></li>
            <li><a href="#">About Us</a></li>
            <li><a href="#">Contact</a></li>
            <li><a href="#">Log out</a></li>
          </ul>
        </nav>
      </div>
      <div className={styles.mapTitleDiv}>
        <p>Your Containers</p>
      </div>
      <div>
        <Image src={img} alt="map" className={styles.mainMap}/>
      </div>
      <div>
        <p className={styles.mapHint}>Click on a container to see details!</p>
      </div>
      <div className={styles.mapButtonDiv}>
        <button className={styles.mapButtons}>Info</button>
        <button className={styles.mapButtons}>Click</button>
        <button className={styles.mapButtons}>Click</button>
        <button className={styles.mapButtons}>Click</button>
      </div>
    </div>
  );
}
