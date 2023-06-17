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
    query: { test, error },
  } = router

  const props = {
    test, error
  };

  const [currentContainerObj, setCurrentContainerObj] = useState(containers[0]);
  const updateConObj = (propCon) => setCurrentContainerObj(propCon);
  useEffect(() => updateConObj(containers[parseInt(props.test, 10) - 1]));
  const isProblem = () => {
    // Idea: instead of containers[], search through containers till it matches container id,
    // then call isProblem() on that container
    //var con1 = containers[parseInt(props.test, 10) - 1]
    var con1 = getConById(parseInt(props.test, 10))

    //var con1 = props.error
    var error = false
    if (con1 != undefined) {
      if (con1.doorStatus == "open") {
        error = true
      } else if (con1.crashed == "True") {
        error = true
      }
    }

    return error
  }
  var isTrueSet = (props.error === 'false')
  // Current TODO: props.error is not yet a useable boolean 
  console.log(props.error)
  console.log(isTrueSet)
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
            <p className={mc.cardTitle}>Removed</p>
          </div>
          <p className={mc.cardValue}>
            <span>Removed</span>
          </p>
        </div>

        <div className={'border-1 p-4 rounded-lg mb-4' + (isProblem() ? 'hover:bg-red-400 bg-red-300 rounded-lg' : 'border bg-white rounded-lg')}>
          <div className={mc.status}>
            <p className={mc.cardTitle}>Door Status:</p>
            <p className={mc.doorStatus} id="doorStatus"></p>
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
