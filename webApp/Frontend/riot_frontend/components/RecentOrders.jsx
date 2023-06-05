import React from 'react'
import Router from "next/router"
import { Button } from "@nextui-org/react"
import { containers } from '../data/container.js'

import Image from 'next/image'
import myLogo from '../assets/RIOT_Sum_2023_Logo.png'
import { Checkbox } from "@nextui-org/react";
import { useState, useEffect } from 'react';
function isProblem(con) {
    var error = false
    if (con != undefined) {
        if (con.doorStatus == "open") {
            error = true
        } else if (con.crashed == "True") {
            error = true
        }
        return error
    }
}
function problemSort(a, b) {
    if (isProblem(a) || isProblem(b)) {
        return -1;
    }
    if (!isProblem(a) || !isProblem(b)) {
        return 1;
    }
    return 0;
}

function reverseProblemSort(a, b) {
    if (isProblem(a) || isProblem(b)) {
        return 1;
    }
    if (!isProblem(a) || !isProblem(b)) {
        return -1;
    }
    return 0;
}

// containers.sort(reverseProblemSort)

// containers.sort(problemSort)




const RecentOrders = () => {
    const [currentContainer, setCurrentContainer] = useState(0);
    const updateCon = (conID) => setCurrentContainer(conID);
    const [IsChecked, setIsChecked] = useState(false);
    const updateChecked = (IsChecked) => setIsChecked(!IsChecked);
    const test = currentContainer
    function sendProps() {
        Router.push({
            pathname: "/dashboard",
            query: {
                test
            }
        });
    }
    function testfunc() {
        if (IsChecked) { // change to whenever IsChecked is incremented/changed
            return containers.sort(problemSort)
        } else {
            return containers
        }
    }
    function getProblem(con) {
        var con = currentContainer;
        var error_message = ""
        // if (con.doorStatus == "open") {
        //     error_message = "Door is open!"
        // } else if (con.crashed == "True") {
        //     error_message = "Ship has Crashed!"
        // }
        return error_message
    }
    var testArray;
    return (
        <div className='w-full col-span-1 relative lg:h-[70vh] h-[50vh] m-auto p-4 border rounded-lg bg-white overflow-scroll '>
            <h1 className='font-bold'>Container List</h1>
            <div className='items-center'>
                <div className='grid grid-cols-4 gap-4"'>

                    <input className="h-5 w-5" placeholder='Sort By Error' type='checkbox' onClick={() => {
                        updateChecked(IsChecked),
                            console.log(IsChecked),
                            testArray = testfunc()
                    }}
                    />
                    <input
                        className="px-5 py-1 w-2/3 sm:px-5 sm:py-3 flex-1 text-zinc-200 bg-gray-200 focus:bg-gray-400 rounded-full focus:outline-none focus:ring-[1px] focus:ring-white placeholder:text-black"
                        placeholder="Start/destination"
                    />
                    <input
                        className="px-5 py-1 w-2/3 sm:px-5 sm:py-3 flex-1 text-zinc-200 bg-gray-200 focus:bg-gray-400 rounded-full focus:outline-none focus:ring-[1px] focus:ring-white placeholder:text-black"
                        placeholder="Content"
                    />
                    <input
                        className="px-5 py-1 w-2/3 sm:px-5 sm:py-3 flex-1 text-zinc-200 bg-gray-200 focus:bg-gray-400 rounded-full focus:outline-none focus:ring-[1px] focus:ring-white placeholder:text-black"
                        placeholder="Search IDs"
                    />
                </div>
            </div>

            <ul>

                {containers.map((con, id) => (
                    <li
                        key={id}
                        onClick={() => {
                            document.getElementById("containerTracker").innerHTML = con.id;
                            document.getElementById("doorStatus").innerHTML = con.doorStatus;
                            setCurrentContainer(con.id)
                            sendProps()
                        }}
                        className={"rounded-lg my-3 p-2 flex items-center cursor-pointer " + (isProblem(con) ? 'hover:bg-red-400 bg-red-300' : 'hover:bg-gray-200 bg-gray-100')

                        }
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
                            <span className='text-gray-500 text-sm'>{con.start}--- </span>
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