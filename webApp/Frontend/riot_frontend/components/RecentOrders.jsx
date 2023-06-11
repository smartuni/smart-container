import React from 'react'
import Router from "next/router"
import { Button } from "@nextui-org/react"
// import { containers } from '../data/container.js'
import { FaShoppingBag } from 'react-icons/fa'
import Image from 'next/image'
import myLogo from '../assets/RIOT_Sum_2023_Logo.png'
import Checkbox from "@/components/Checkbox";
import { useState, useEffect } from 'react';
function isProblem(con) {
    var error = false
    if (con != undefined) {
        if (con.container_door_closed == "open") {
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






const RecentOrders = ({ containers }) => {
    const [currentContainer, setCurrentContainer] = useState(0);
    const updateCon = (conID) => setCurrentContainer(conID);
    const [isError, setIsError] = useState(false);
    const updateError = () => setIsError(!isError)
    const test = currentContainer
    function sendProps() {
        Router.push({
            pathname: "/dashboard",
            query: {
                test
            }
        });
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

    return (
        <div className='w-full col-span-1 relative lg:h-[70vh] h-[50vh] m-auto p-4 border rounded-lg bg-white overflow-scroll '>
            <h1 className='font-bold'>Container List</h1>
            <div className='items-center'>
                <div className='grid grid-cols-4 gap-4"'>

                    <Checkbox label="Sort by errors" id="Error checkbox id" />
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
                {containers.map((con) => (
                    // render containers data
                    <li
                        key={con.container_id}
                        onClick={() => {
                            document.getElementById("containerTracker").innerHTML = con.container_id;
                            document.getElementById("doorStatus").innerHTML = con.container_door_closed;
                            setCurrentContainer(con.container_id)
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
                            <p className='text-gray-800 font-bold'>Container id: {con.container_id}</p>
                            <span className='text-gray-500 text-sm'>{con.container_start}--- </span>
                            <span className='text-gray-500 text-sm'>{con.container_destination}</span>
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