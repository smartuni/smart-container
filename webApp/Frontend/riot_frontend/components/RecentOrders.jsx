import React from 'react'

import {containers} from '../data/container.js'
import {FaShoppingBag} from 'react-icons/fa'
import Image from 'next/image'
import myLogo from '../assets/RIOT_Sum_2023_Logo.png'

function isProblem(con) {
    var error = false
    if(con.doorStatus == "open") {
        error = true
    } else if(con.crashed == "True") {
        error = true
    } 
    return error
}

function getProblem(con) {
    var error_message = ""
    if(con.doorStatus == "open") {
        error_message = "Door is open!"
    } else if(con.crashed == "True") {
        error_message = "Ship has Crashed!"
    } 
    return error_message
}
const RecentOrders = () => {
    return (
        <div className='w-full col-span-1 relative lg:h-[70vh] h-[50vh] m-auto p-4 border rounded-lg bg-white overflow-scroll '>
            <h1>Container List</h1>
            <ul>
                {containers.map((con, id) => (
                    <li 
                    key={id} 
                    className={"rounded-lg my-3 p-2 flex items-center cursor-pointer " + (isProblem(con) ? 'hover:bg-red-400 bg-red-300' : 'hover:bg-gray-200 bg-gray-100')}
                    >
                
                        <div className='bg-purple-100 rounded-lg p-3'>
                        <Image
                            className=' w-10'
                            src={myLogo}
                            alt="Picture of the author"
                            
                             // layout="fill", layout="intrinsic" 
                        />
                        </div>
                        <div className='pl-4'>
                            <p className='text-gray-800 font-bold'>Container id: {con.id}</p>
                            <span className='text-gray-500 text-sm'>{con.start}---</span>
                            <span className='text-gray-500 text-sm'>{con.dest}</span>
                        </div>
                        <div className='items-center'>
                            <p className={'text-lg font-bold mx-auto justify-between px-10 pt-4' + (isProblem(con) ? 'hidden' : 'flex')}>
                                {getProblem(con)}
                            </p>
                        </div>
                        
                    </li>
                

                ))}
            </ul>
        </div>
    )
}
export default RecentOrders