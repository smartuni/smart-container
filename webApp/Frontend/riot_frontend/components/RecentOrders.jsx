import React from 'react'
import Router from "next/router"
import { Button } from "@nextui-org/react"
// import { containers } from "../data/container"

import Image from 'next/image'
import myLogo from '../assets/RIOT_Sum_2023_Logo.png'
import { Checkbox } from "@nextui-org/react";
import { useState, useEffect, useRef } from 'react';
import { getServerSideProps } from '@/pages/dashboard'


function isProblem(con) {
    var error = false
    //console.log("undefined check for con: " + typeof con)
    if (con != undefined) {
        if (con.container_door_closed == false) { // should be == false
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




const RecentOrders = ({ containers, location }) => {
    const [currentContainer, setCurrentContainer] = useState(0);

    const [list, setList] = useState(containers)


    const updateCon = (conID) => setCurrentContainer(conID);
    const [IsChecked, setIsChecked] = useState(false);
    const updateChecked = () => {
        setIsChecked(!IsChecked);
    }

    const [messageLoc, setMessageLoc] = useState('')
    const handleChangeLoc = (event) => {
        setMessageLoc(event.target.value)
    }


    const [updated, setUpdated] = useState(messageLoc)
    const [messageID, setMessageID] = useState('')
    const handleChangeID = (event) => {
        setMessageID(event.target.value)
    }
    const [updatedID, setUpdatedID] = useState(messageID)
    const handleClickLoc = () => {
        setUpdated(messageLoc)
    }

    const handleClickID = () => {
        setUpdatedID(messageID)
    }


    var newList = containers

    function sendProps() {
        const test = currentContainer
        var error = isProblem(test)

        Router.push({
            pathname: "/dashboard",
            query: {
                test, error,
            }
        });
    }
    // Code below is from Emily
    // sensorData is all sensor data
    // returns latest location data

    // let containerLocations = sensorData.filter((sensor) => sensor.container_id == container_id && sensor.sensor_type == "GPS")
    //     let latestcontainerLocations = containerLocations.reduce((latest, current) => {
    //         if (latest.timestamp > current.timestamp) {
    //         return latest
    //         } else {
    //          return current
    //         }
    // })

    console.log("containers list?: ", containers)
    console.log(typeof containers)
    function testfunc() {
        if (IsChecked) { // change to whenever IsChecked is incremented/changed
            return newList.sort(problemSort)
        } else {
            return newList
        }
    }
    var testArray;


    const renderAuthButton = () => {
        // If access token is expired, this function will throw an error!
        if (containers != undefined) {


            if (updated === "" && updatedID === "") {
                return containers
            } else if (updated != "" && updatedID === "") {

                var tempList = list.filter((item) => item.container_start == updated
                    || item.container_destination.includes(updated)
                    || item.container_content.includes(updated))
                // || item.id === updated)
                return tempList

            } else if (updated === "" && updatedID != "") {
                return list.filter((item) => item.container_id == updatedID)

            } else {
                console.log("else reached")
                var tempList2 = list.filter((item) => item.container_start == updated
                    && item.container_id === updatedID
                    || item.container_destination.includes(updated)
                    && item.container_id === updatedID
                    || item.container_content.includes(updated)
                    && item.container_id === updatedID)
                return tempList2

            }
        }

    }



    return (
        <div className='w-full relative lg:h-[70vh] h-[50vh] m-auto p-4 border rounded-lg bg-white overflow-scroll '>
            <h1 className='font-bold'>Container List</h1>
            <div className='items-center '>
                <span className=''>sort by error</span>
                <input type='checkbox' className="h-6 w-6 ml-2" placeholder="Sort By Error" checked={IsChecked} onClick={() => {
                    updateChecked(),
                        console.log(IsChecked),
                        testArray = testfunc()
                }}
                />
                <div className='grid grid-rows-2'>

                    <div class="relative text-gray-600 focus-within:text-gray-400 p-4">
                        <span class="absolute inset-y-0 left-0 flex items-center pl-2">
                            <button
                                type="submit"
                                class=" focus:outline-none focus:shadow-outline p-4">
                                <svg
                                    fill="none"
                                    stroke="currentColor"
                                    stroke-linecap="round"
                                    stroke-linejoin="round"
                                    stroke-width="2"
                                    viewBox="0 0 24 24"
                                    class="w-6 h-6">
                                    <path d="M21 21l-6-6m2-5a7 7 0 11-14 0 7 7 0 0114 0z"></path>
                                </svg>
                            </button>
                        </span>
                        <input
                            type="search"
                            name="q" class="py-2 text-sm text-black bg-malibu-300 rounded-md pl-10 focus:outline-none focus:bg-gray-200 focus:text-gray-900 w-full h-full"
                            placeholder="Search Start/Dest & content"
                            autocomplete="off"
                            onChange={handleChangeLoc}
                            value={messageLoc} />
                    </div>



                    <div class="relative text-gray-600 focus-within:text-gray-400 p-4">
                        <span class="absolute inset-y-0 left-0 flex items-center pl-2">
                            <button
                                type="submit"
                                class=" focus:outline-none focus:shadow-outline p-4">
                                <svg
                                    fill="none"
                                    stroke="currentColor"
                                    stroke-linecap="round"
                                    stroke-linejoin="round"
                                    stroke-width="2"
                                    viewBox="0 0 24 24"
                                    class="w-6 h-6">
                                    <path d="M21 21l-6-6m2-5a7 7 0 11-14 0 7 7 0 0114 0z"></path>
                                </svg>
                            </button>
                        </span>
                        <input
                            type="search"
                            name="q" class="py-2 text-sm text-black bg-malibu-300 rounded-md pl-10 focus:outline-none focus:bg-gray-200 focus:text-gray-900 w-full h-full"
                            placeholder="Search by ID..."
                            autocomplete="off"
                            onChange={handleChangeID}
                            value={messageID} />
                    </div>
                    <Button className='col-span-2' bordered color="primary" auto type='submit'
                        onPress={() => {
                            handleClickLoc()
                            handleClickID()
                            // handleSortByLocation(updatedID)
                            //console.log(updated)
                            //console.log(typeof updated)
                        }}>Refresh</Button>
                </div>
            </div>

            <ul>

                {renderAuthButton().map((con, id) => (
                    <li
                        key={con.container_id}
                        onClick={() => {
                            document.getElementById("containerTracker").innerHTML = con.container_id;
                            document.getElementById("doorStatus").innerHTML = con.container_door_closed;
                            updateCon(con.container_id)

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
                        <div className='p-2'>


                            <div className=''>
                                <p className='text-gray-800 font-bold'>Container id: {con.container_id}</p>
                                <span className='text-gray-500 text-sm'>{con.container_start}--- </span>
                                <span className='text-gray-500 text-sm'>{con.container_destination}</span>
                            </div>

                            <div className='text-gray-500 text-sm'>
                                {con.container_content}
                            </div>

                        </div>
                    </li>


                ))}
            </ul>
        </div>
    )
}

// TODO getServerSideProps
export default RecentOrders

