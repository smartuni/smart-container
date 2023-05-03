import { useState } from 'react';
import { useRouter } from "next/router";
import styles from '/styles/map.module.css'
//import { MapContainer, TileLayer, Marker, Popup } from 'react-leaflet';
import Image from "next/image";
import img from "/public/Map2.png";

export default function MapPage() {
    return (
      <div >
          <nav style={{ display: 'flex', justifyContent: 'flex-end', padding: '1rem'}}>
              <ul>
                  <li><a href="/">Home</a></li>
                  <li><a href="#">About Us</a></li>
                  <li><a href="#">Contact</a></li>
                  <li><a href="#">Log out</a></li>
              </ul>
          </nav>
          <div style={{ flex: '1', display: 'flex', flexDirection: 'row' }}>
              <div className={styles.sideBar} >
                  <div style={{ marginTop: '50px' }}>
                      <span style={{ cursor: 'default' }}>Information 1</span>
                  </div>
                  <div >
                      <span style={{ cursor: 'default' }}>Information 2</span>
                  </div>
                  <div >
                      <span style={{ cursor: 'default' }}>Information 3</span>
                  </div>
                  <div >
                      <span style={{ cursor: 'default' }}>Information 4</span>
                  </div>
              </div>
              <div style={{ flex: '1', display: 'flex', flexDirection: 'column' }}>
                  <div style={{ textAlign: 'center'}}>
                      <h2>Containers</h2>
                  </div>
                  <div style={{ flex: '1', position: 'relative' }}>
                      <Image src={img} alt="map" style={{width: '90%', flexGrow: '1' }}/>
                  </div>
                  <div style={{ textAlign: 'center'}}>
                      <h2>Click on a container to see details!</h2>
                  </div>
              </div>
        </div>
  
      </div>
    );
  }
  