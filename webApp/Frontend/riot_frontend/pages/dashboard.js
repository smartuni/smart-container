import TempChart from "./temperature";
import Head from 'next/head';
import Image from 'next/image';
import Header from '../components/Header';
import TopCards from "@/components/TopCards";
import BarChart from "@/components/BarChart";
import RecentOrders from "@/components/RecentOrders";
import {containers} from '../data/container.js';
import {FaShoppingBag} from 'react-icons/fa';
import { useState, useEffect } from 'react';
import myLogo from '../assets/RIOT_Sum_2023_Logo.png';
import Document, { Html, Main, NextScript } from 'next/document'



const DEFAULT_CENTER = [53.5511, 9.9937];
const markers = [
  { name: 'Container 1', location: [53.55587, 10.02439] },
  { name: 'Container 2', location: [53.55513463677272, 9.992930792175889] },
  { name: 'Container 3', location: [53.53952514227034, 10.0049117958243] },
];






const Home = () => {
  const [showMe, setShowMe] = useState(false);
  const [currentContainer, setCurrentContainer] = useState(0);
  var myArray = [];
  var indexes = [];
  var ele;
function toggle() {
  
  
  setShowMe(!showMe);
}

const updateCon = (conID) => setCurrentContainer(conID);
  
const isProblem = (con) => {
  var error = false
  if(con.doorStatus == "open") 
  {
    error = true
  } else if(con.crashed == "True")
  {
    error = true
  }
  
  return error
}


const getConById = (Id) => {
  var result = containers.find(item => item.id == Id);
  return result
}


const getProblem = (container) => {
  var error_message = ""
  if(container.doorStatus == "open") {
      error_message = "Door is open!"
  } else if(container.crashed == "True") {
      error_message = "Ship has Crashed!"
  } 
  return error_message
}


function bundle(conID) {
  updateCon(conID);
  indexes.push(conID)
  toggle();
}
 
function getCurrentContainer() {
  return currentContainer
}
  

  return (
    <>
    <Head>
      <title>Create Next App</title>
      <meta name='description' content='Generated to create next app'/>
      <meta name='viewport' content='width=device-width, initial-scale=1'/>
      <link rel='icon' href='/favicon.ico'/>
    </Head>
    <main className=' bg-malibu-500 min-h-screen'>
      <Header/>
      {/*Top Cards------------------------------------------------------------------ */}
      {/*<TopCards/>*/}
      <div>
        
      
        <div className='grid lg:grid-cols-6 lg:grid-rows-2 gap-4 p-4'>
        
              <div className='lg:col-span-6 col-span-1 bg-white flex justify-between w-full border p-4 rounded-lg'>
                  <div className='flex justify-center items-center flex-col w-full pb-4'>
                  
                    <div>
                      <span className='text-2xl font-bold'>Container Id:</span> 
                      <span className="text-2xl ml-2 font-bold" id="IdLabel"></span>
                    </div>
                    
                  </div>
                  
              </div>

              <div className=' bg-white flex justify-between w-full border p-4 rounded-lg'>
                  <div className='flex flex-col w-full pb-4'>
                      <p className='text-2xl font-bold'>Current Humidity:</p>
                      
                  </div>
                  <p className='bg-green-200 flex justify-center items-center p-1 rounded-lg'>
                      <span className='text-green-700 text-lg' id="humidityLabel"></span>
                  </p>
              </div>

              <div className='bg-white flex justify-between w-full border p-4 rounded-lg'>
                  <div className='flex flex-col w-full pb-4'>
                      <p className='text-2xl font-bold'>Acceleration:</p>
                      
                  </div>
                  <p className='bg-green-200 flex justify-center items-center p-2 rounded-lg'>
                      <span className='text-green-700 text-lg' id="accelerationLabel"></span>
                  </p>
              </div>

              <div className={'flex justify-between w-full p-4' + (isProblem(getConById(currentContainer)) ? 'hover:bg-red-400 bg-red-300 rounded-lg' : 'border bg-white rounded-lg')}> 
                  <div className='flex flex-col w-full pb-4'>
                      <p className='text-2xl font-bold'>Door Status:</p>
                      <p className='text-green-600 text-2xl' id="doorStatusLabel"></p>
                      <p className='text-2xl font-bold'>Last Opened:</p>
                      <p className='text-2xl' id="lastOpenedLabel"></p>
                  </div>
                  
              </div>

              <div className='bg-white flex justify-between w-full border p-4 rounded-lg'>
                  <div className='flex flex-col w-full pb-4'>
                      <p className='text-2xl font-bold'>Temperature:</p>
                      
                  </div>
                  <p className='bg-green-200 flex justify-center items-center p-2 rounded-lg'>
                      <span className='text-green-700 text-lg' id="tempLabel"></span>
                  </p>
              </div>

              <div className={'flex justify-between w-full p-4 rounded-lg' + (isProblem(getConById(currentContainer)) ? 'hover:bg-red-400 bg-red-300 rounded-lg' : 'border bg-white rounded-lg')}>
                  <div className='flex flex-col w-full pb-4'>
                      <p className='text-2xl font-bold text-green-600' id="crashedLabel"></p>
                      
                  </div>
                  
              </div>

              <div className='bg-white flex justify-between w-full border p-4 rounded-lg'>
                  <div className='flex flex-col w-full pb-4'>
                      <p className='text-2xl font-bold text-green-600' id="contentLabel"></p>
                      
                  </div>
                  
              </div>

          </div>
        </div>
      {/*------------------------------------------------------------------- */}
      
      <div>

      </div>
      <div className="p-4 grid md:grid-cols-3 grid-cols-1 gap-4">


      {/* <Map  width="100%" height="400" center={DEFAULT_CENTER} zoom={12}>
          {({ TileLayer, Marker, Popup }) => (
            <>
              <TileLayer
                url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
                attribution="&copy; <a href=&quot;http://osm.org/copyright&quot;>OpenStreetMap</a> contributors"
              />
              {markers.map((marker, index) => (
                <Marker key={index} position={marker.location}>
                  <Popup>
                    {marker.name}
                  </Popup>
                </Marker>
              ))}

            </>
          )}
        </Map> */}

      <div className='w-full col-span-1 static lg:h-[70vh] h-[50vh] m-auto p-4 border rounded-lg bg-white overflow-scroll '>
                  <h1>RecentOrders</h1>
                  <ul>
                      {containers.map((con, id) => (
                          
                          <li 
                          key={id} 
                          onClick={()=> {
                            updateCon(con.id)
                            document.getElementById("IdLabel").innerHTML=con.id;
                            document.getElementById("tempLabel").innerHTML="con " + con.id + " temp";
                            document.getElementById("humidityLabel").innerHTML="con " + con.id + " humidity";
                            document.getElementById("accelerationLabel").innerHTML="con " + con.id + " acceleration";
                            document.getElementById("doorStatusLabel").innerHTML=con.doorStatus;
                            document.getElementById("lastOpenedLabel").innerHTML="con " + con.id + " last opened";
                            document.getElementById("crashedLabel").innerHTML="Crashed " + con.crashed;
                            document.getElementById("contentLabel").innerHTML=con.content;
                        
                          }}
                          // onClick={Document.getElementById("test").innerHTML="Container id: " + con.id}
                          //onClick={document.getElementById("test").innerHTML="Container id: " + con.id}
                          onHo
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
      </div>
    </main>
    </>
  )
}
export default Home;
