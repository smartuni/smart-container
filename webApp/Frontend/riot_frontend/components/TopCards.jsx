import React from 'react';
import TempChart from "../pages/temperature";
import mc from './TopCards.module.css';
// import { containers } from '../data/container.js'
import { useState, useEffect } from "react";
import { useRouter } from "next/router"

// This data should be from sensors
const tempData = [
  { time: '12:00', temperature: 23 },
  { time: '12:30', temperature: 24 },
  { time: '13:00', temperature: 26 },
  { time: '13:30', temperature: 25 },
  { time: '14:00', temperature: 23 },
];
const getConById = (Id) => {
  var result = containers.find(item => item.id == Id);
  return result
}


// const Cards = classNames('flex justify-between w-full p-4 rounded-lg' + (isProblem(getConById(currentContainer)) ? 'hover:bg-red-400 bg-red-300 rounded-lg' : 'border bg-white rounded-lg'));

// Temperature, Humidity, GPS, Tamper, Acceleration
const TopCards = ({ containers }) => {
  const router = useRouter()

  const {
    query: { test, error },
  } = router

  const props = {
    test, error
  };

  // const [currentContainerObj, setCurrentContainerObj] = useState(containers[0]);
  const updateConObj = (propCon) => setCurrentContainerObj(propCon);
  // useEffect(() => updateConObj(containers[parseInt(props.test, 10) - 1]));

  var isTrueSet = (props.error === 'true') // fix line (doesnt change !!!)
  // Current TODO: props.error is not yet a useable boolean 
  // console.log("props.error is currently: ", props.error) // For some reason props.error is always false
  // console.log("props.test is currently: " + props.test)
  // console.log("props.test.content type is: ", typeof props.test.content)
  // console.log(isTrueSet)
  // console.log(isProblem(containers[parseInt(props.test, 10) - 1]))
  function isProblem(con_array, containerId) {
    var error = false

    // console.log("undefined check for con: " + typeof con_array)

    var tempList = con_array.filter((item) => item.container_id == containerId)
    console.log("tempList is currently: ", tempList)
    return error


  }
  return (
    <div>

      <div className='flex justify-center items-center '>
        <div className='col-span-1 bg-white h-full w-2/12 flex justify-center rounded-lg border items-center font-bold font-xl'>
          <div className=''>Current Container Id:
            <div>
              <p className='font-bold font-xl' id="containerTracker">1</p>
            </div>
          </div>
        </div>
      </div>

      <div className='grid lg:grid-cols-6 grid-rows-1 gap-4 p-4'>
        {/* New card that checks if there was a crash? */}

        <div className={mc.card}>
          <div>
            {/* Newest timestamp goes here (OR CURRENT LOCATION COORDINATES) */}
            <p className={mc.cardTitle}>Sensors last updated:</p>
          </div>
          <p className={mc.newValue}>
            <span id="container_time_stamp">---</span>
          </p>
        </div>


        <div className={mc.card}>
          <div>
            <div>
              <p className={mc.cardTitle}>Current Temp:</p>
            </div>
            <div style={{ width: '105%' }}>
              <TempChart data={tempData} />
            </div>
          </div>
          {/* Get temp from sensor data */}
          {/* <p className={mc.temperature}>20.1C</p> */}
        </div>


        <div className={mc.card}>
          <div>
            <p className={mc.cardTitle}>Current Humidity:</p>
          </div>
          <p className={mc.newValue}>
            {/* Get humidity from sensor data */}
            <span>50%</span>
          </p>
        </div>


        <div className={'border-1 p-4 rounded-lg mb-4' + (isTrueSet ? 'hover:bg-red-400 bg-red-300 rounded-lg' : 'border bg-white rounded-lg')}>
          <div className={mc.status}>
            <p className={mc.cardTitle}>Door Closed:</p>
            <p className={mc.newValue} id="doorStatus">---</p>
            <p className={mc.cardTitle}>Last Opened:</p>
            {/* Redundant timestamp? */}
            <p className={mc.newValue}>23/02/23 12pm</p>
          </div>
        </div>

        <div className={mc.card}>
          <div className={mc.status}>
            <p className={mc.cardTitle}>Leak Status:</p>
            <p className={mc.newValue} id="leak status">---</p>

          </div>
        </div>
        <div className={mc.card}>
          <div className={mc.status}>
            <p className={mc.cardTitle}>Acceleration:</p>
            <p className={mc.newValue} id="acceleration id">---</p>

          </div>
        </div>

      </div>
    </div>
  );
};

export default TopCards;
