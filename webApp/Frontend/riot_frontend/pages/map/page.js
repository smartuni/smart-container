import React from "react";
import Link from "next/link";
//import styles from '../styles/map.module.css'
import Image from "next/image";
import img from "/public/Map2.png";

export default function Map() {
  return (
    <div>
      <div>
        <nav >
          <ul>
            {/* <li><a href="/">Home</a></li> */}
            <li><a href="/home">Home</a></li>
            <li><a href="about">About Us</a></li>
            <li><a href="#">Contact</a></li>
            <li><a href="#">Log out</a></li>
          </ul>
        </nav>
      </div>
      <div className="mapTitleDiv">
        <p>Your Containers</p>
      </div>
      <div>
        <Image src={img} alt="map" className="mainMap" />
      </div>
      <div>
        <p className="mapHint">Click on a container to see details!</p>
      </div>
      <div className="mapButtonDiv">
        <button className="mapButtons">Click</button>
        <button className="mapButtons">Click</button>
        <button className="mapButtons">Click</button>
        <button className="mapButtons">Click</button>
      </div>
    </div>
  );
}
