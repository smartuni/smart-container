import React from 'react';
import TempChart from "../pages/temperature";
import mc from './TopCards.module.css';


const tempData = [
  { time: '12:00', temperature: 23 },
  { time: '12:30', temperature: 24 },
  { time: '13:00', temperature: 26 },
  { time: '13:30', temperature: 25 },
  { time: '14:00', temperature: 23 },
];

const TopCards = () => {
  return (
    <div>

      <div className='flex justify-center items-center '>
        <div className='col-span-1 bg-white h-full w-3/12 flex justify-center rounded-lg border items-center font-bold font-xl'>Current Container Id:
          <span className='font-bold font-xl'>1</span></div>
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

        <div className={mc.card}>
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
