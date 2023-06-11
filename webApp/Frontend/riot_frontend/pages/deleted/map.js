import React from "react";
import Link from "next/link";
import styles from '../styles/map.module.css'
import Image from "next/image";
import { useEffect } from 'react';
import Leaflet from 'leaflet';
import * as ReactLeaflet from 'react-leaflet';

export default function Map() {
  return (
    <div>
      <nav>
          <ul>
            <li><a href="/">Home</a></li>
            <li><a href="/about">About Us</a></li>
            <li><a href="/contact">Contact</a></li>
            <li><a href="#">Log out</a></li>
          </ul>
      </nav>
      <div className={styles.containersInfo}>
        <div>Info1</div>
        <div>Info2</div>
        <div>Info3</div>
        <div>Info4</div>
      </div>
      <div className={styles.map}>
          <p className={styles.mapHint}>Your Containers</p>
          <Image src={img} alt="map" className={styles.mainMap}/>
          <p className={styles.mapHint}>Click on a container to see details!</p>
      </div>
    </div>
  );
}
