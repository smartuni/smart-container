import React from 'react'
import BarChart from "./barchart";
import TempChart from "../pages/temperature"; 

const tempData = [
    { time: '12:00', temperature: 23 },
    { time: '12:30', temperature: 24 },
    { time: '13:00', temperature: 26 },
    { time: '13:30', temperature: 25 },
    { time: '14:00', temperature: 23 },
  ];


const TopCards = () => {
    return (
        <div className='grid lg:grid-cols-5 gap-4 p-4'>       
            <div className='bg-white flex justify-between w-full border p-4 rounded-lg'>
                <div className='flex flex-col w-full'>
                    <div className='flex flex-col w-full'>
                        <p className='text-2xl font-bold'>Current Temp:</p>                  
                    </div>
                    <div className='flex justify-center items-center' style={{ width: '80%' }}>
                        <TempChart data={tempData} />
                    </div>
                </div>
                <p className='bg-green-200 flex justify-center items-center p-2 rounded-lg' style={{ position: "relative", left:"-60px" }}>
                    <span className='text-green-700 text-lg'>20,1C</span>
                </p>
            </div>

            <div className=' bg-white flex justify-between w-full border p-4 rounded-lg'>
                <div className='flex flex-col w-full pb-4'>
                    <p className='text-2xl font-bold'>Current Humidity:</p>
                    
                </div>
                <p className='bg-green-200 flex justify-center items-center p-1 rounded-lg'>
                    <span className='text-green-700 text-lg'>50%</span>
                </p>
            </div>

            <div className='bg-white flex justify-between w-full border p-4 rounded-lg'>
                <div className='flex flex-col w-full pb-4'>
                    <p className='text-2xl font-bold'>Acceleration:</p>
                    
                </div>
                <p className='bg-green-200 flex justify-center items-center p-2 rounded-lg'>
                    <span className='text-green-700 text-lg'>10km/h</span>
                </p>
            </div>

            <div className='bg-white flex justify-between w-full border p-4 rounded-lg'>
                <div className='flex flex-col w-full pb-4'>
                    <p className='text-2xl font-bold'>Door Status:</p>
                    <p className='text-green-600 text-2xl'>Closed</p>
                    <p className='text-2xl font-bold'>Last Opened:</p>
                    <p className='text-2xl'>23/02/23 12pm</p>
                </div>
                
            </div>

            <div className='bg-white flex justify-between w-full border p-4 rounded-lg'>
                <div className='flex flex-col w-full pb-4'>
                    <p className='text-2xl font-bold text-green-600'>No water leak detected</p>
                    
                </div>
                
            </div>

        </div>
    )
}

export default TopCards