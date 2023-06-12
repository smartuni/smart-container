import React from 'react'
import Router from "next/router"
import { Button } from "@nextui-org/react"
import { containers } from '../data/container.js'

import Image from 'next/image'
import myLogo from '../assets/RIOT_Sum_2023_Logo.png'
import { Checkbox } from "@nextui-org/react";
import { useState, useEffect, useRef } from 'react';


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
    const [list, setList] = useState(containers)
    const updateCon = (conID) => setCurrentContainer(conID);
    const [IsChecked, setIsChecked] = useState(false);
    const updateChecked = () => {
        setIsChecked(!IsChecked);
    }

    const [message, setMessage] = useState('')
    const handleChange = (event) => {
        setMessage(event.target.value)
    }
    const [updated, setUpdated] = useState(message)
    const handleClick = () => {
        setUpdated(message)
    }

    const test = currentContainer
    var newList = containers
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
            return newList.sort(problemSort)
        } else {
            return newList
        }
    }

    function handleSortByLocation(updated) {
        // newList = list.filter((item) => item.start != updated && item.dest != updated);
        newList = containers
        // if (newList.length === 0) {
        //     return containers
        // } else {
        //     for (const ele of containers) {
        //         if (ele.start != updated && ele.dest != updated) {
        //             newList.pop(ele)
        //         }
        //     }
        // }


        return newList
    }

    const renderAuthButton = () => {

        if (updated === "") {
            return containers
        } else {

            var tempList = list.filter((item) => item.start == updated || item.dest == updated);
            return tempList

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

                    <input type='checkbox' className="h-8 w-8" placeholder="Sort By Error" id="checkbox" checked={IsChecked} onClick={() => {
                        updateChecked(),
                            console.log(IsChecked),
                            testArray = testfunc()
                    }}
                    />

                    <input
                        className="px-5 py-1 w-2/3 sm:px-5 sm:py-3 flex-1 text-zinc-200 bg-gray-200 focus:bg-gray-400 rounded-full focus:outline-none focus:ring-[1px] focus:ring-white placeholder:text-black text-red-700"
                        placeholder="Start/destination"

                        type='text'
                        id="start/dest"
                        name="start/dest"
                        onChange={handleChange}
                        value={message}
                    />
                    <input
                        className="px-5 py-1 w-2/3 sm:px-5 sm:py-3 flex-1 text-zinc-200 bg-gray-200 focus:bg-gray-400 rounded-full focus:outline-none focus:ring-[1px] focus:ring-white placeholder:text-black"
                        placeholder="Content"
                    />
                    <input
                        className="px-5 py-1 w-2/3 sm:px-5 sm:py-3 flex-1 text-zinc-200 bg-gray-200 focus:bg-gray-400 rounded-full focus:outline-none focus:ring-[1px] focus:ring-white placeholder:text-black"

                        placeholder="Search IDs"
                    />
                    <Button className='col-span-4 mt-6' bordered color="primary" auto type='submit'
                        onPress={() => {
                            handleClick()
                            handleSortByLocation(updated)
                            console.log(updated)
                            console.log(typeof updated)
                        }}>{updated}</Button>
                </div>
            </div>

            <ul>

                {renderAuthButton().map((con, id) => (
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