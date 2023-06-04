import React from 'react';
import TempChart from "../pages/temperature";
import mc from './TopCards.module.css';
import { containers } from '../data/container.js'
import { useState, useEffect } from "react";
import { useRouter } from "next/router"

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

const TopCards = () => {
  const router = useRouter()

  const {
    query: { test },
  } = router

  const props = {
    test,
  };

  const [currentContainerObj, setCurrentContainerObj] = useState(containers[0]);
  const updateConObj = (propCon) => setCurrentContainerObj(propCon);
  useEffect(() => updateConObj(containers[parseInt(props.test, 10) - 1]));
  const isProblem = () => {
    var con1 = containers[parseInt(props.test, 10) - 1]
    var error = false
    if (con1 != undefined) {
      if (con1.doorStatus == "open") {
        error = true
      } else if (con1.crashed == "True") {
        error = true
      }
    }
    // var con1 = containers[0].doorStatus
    // var con2 = containers[0].crashed
    // if (parseInt(props.test, 10) - 1 != undefined) {

    //   if (typeof containers[0].doorStatus === undefined || typeof containers[0].crashed === undefined) {
    //     console.log("2nd if reached")
    //     if (con1 === "open" || con2 === "True") {
    //       console.log("3rd if reached")
    //       error = true
    //       return error
    //     }
    //   }
    //   else {
    //     console.log("else reached")
    //     con1 = containers[parseInt(props.test, 10) - 1]
    //     if (currentContainerObj.doorStatus === "open" || currentContainerObj.crashed === "True") {
    //       console.log("4th if reached")
    //       error = true
    //       return error
    //     }
    //   }
    // }


    return error

  }
  console.log(typeof (parseInt(props.test, 10)));

  // console.log(isProblem(containers[parseInt(props.test, 10) - 1]))



  return (
    <div>

      <div className='flex justify-center items-center '>
        <div className='col-span-1 bg-white h-full w-3/12 flex justify-center rounded-lg border items-center font-bold font-xl'>Current Container Id:
          <span className='font-bold font-xl' id="containerTracker">1</span></div>
      </div>

      <div className='grid lg:grid-cols-5 grid-rows-1 gap-4 p-4'>

        <div className={mc.card}>
          <div>
            <div>
              <p className={mc.cardTitle}>Current Temp:</p>
            </div>
            <div style={{ width: '80%' }}>
              <TempChart data={tempData} />
            </div>
          </div>
          <p className={mc.temperature}>20.1C</p>
        </div>


        <div className={mc.card}>
          <div>
            <p className={mc.cardTitle}>Current Humidity:</p>
          </div>
          <p className={mc.cardValue}>
            <span>50%</span>
          </p>
        </div>

        <div className={mc.card}>
          <div>
            <p className={mc.cardTitle}>Acceleration:</p>
          </div>
          <p className={mc.cardValue}>
            <span>10km/h</span>
          </p>
        </div>

        <div className={'border-1 p-4 rounded-lg mb-4' + (isProblem() ? 'hover:bg-red-400 bg-red-300 rounded-lg' : 'border bg-white rounded-lg')}>
          <div className={mc.status}>
            <p className={mc.cardTitle}>Door Status:</p>
            <p className={mc.doorStatus}>Closed</p>
            <p className={mc.cardTitle}>Last Opened:</p>
            <p className={mc.lastOpened}>23/02/23 12pm</p>
          </div>
        </div>

        <div className={mc.card}>
          <div>
            <p className={mc.cardTitle}>No water leak detected</p>
          </div>
        </div>
      </div>
    </div>
  );
};

export default TopCards;
