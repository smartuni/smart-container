import TempChart from "./temperature";
import Head from 'next/head';
import Image from 'next/image';
import Header from '../components/Header';
import TopCards from "@/components/TopCards";
import RecentOrders from "@/components/RecentOrders";
import { ContainersMap } from "@/components/Map/ContainersMap";
import { useEffect, useState } from "react";
import axios from "axios";
import { axiosInstance } from "@/utils/axiosInstance";
import { useContainers } from "@/hooks/useContainers";
//import  ContainerProblem from "./containerProblem";

const Home = (props) => {


  return (
    <>
      <Head>
        <title>Create Next App</title>
        <meta name='description' content='Generated to create next app' />
        <meta name='viewport' content='width=device-width, initial-scale=1' />
        <link rel='icon' href='/favicon.ico' />
      </Head>

      <main className=' bg-malibu-500 min-h-screen'>
        <Header />
        <TopCards containers={props.containers} />
        <div className="p-4 grid md:grid-cols-2 grid-cols-1 gap-4">
          <ContainersMap containers={props.containers} />
          <RecentOrders containers={props.containers} location={props.location} date={props.date} />
          {/* <ContainerProblem/> */}
        </div>
      </main>
    </>
  )


}

export default Home


// GetServerSideProps
// const containers = useContainers() 
export const getServerSideProps = async (context) => {

  const res2 = await fetch("http://178.128.192.215:8000/api/signIn/refresh/", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",

    },
    body: JSON.stringify({
      refresh: "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoicmVmcmVzaCIsImV4cCI6MTY4Nzc5ODgyNiwiaWF0IjoxNjg3NzEyNDI2LCJqdGkiOiI3ODliNDEyNmVhNmQ0MDFmYWQ3NjFlNWY1ZjZmNTA0MyIsInVzZXJfaWQiOiJkMDY5OTEzNS0wMjcxLTQ2N2UtYjA1Mi03NmM0N2ViMzliOTUiLCJ1c2VybmFtZSI6ImVtaWx5bHVjaWEuYW50b3NjaEBoYXdoYW1idXJnLmRlIiwiZmlyc3ROYW1lIjoiRW1pbHkiLCJsYXN0bmFtZSI6IkFudG9zY2gifQ.37wWnzKr02lm8RgSm01lgwq6bhaRR4rV8EPDRcvdcIA"
    })
  }).then((res) => {
    return res.json();
  }).then((response) => {
    const res = fetch("http://178.128.192.215:8000/api/container/", {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        "Authorization": "Bearer " + response["access"]
      },
    });
    console.log("Containers are fetched!");
    return res
  })


  // The code below is a bit redundant, but gets the location, not yet as an array
  const locationTest = await fetch("http://178.128.192.215:8000/api/signIn/refresh/", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",

    },
    body: JSON.stringify({
      refresh: "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoicmVmcmVzaCIsImV4cCI6MTY4Nzc5ODgyNiwiaWF0IjoxNjg3NzEyNDI2LCJqdGkiOiI3ODliNDEyNmVhNmQ0MDFmYWQ3NjFlNWY1ZjZmNTA0MyIsInVzZXJfaWQiOiJkMDY5OTEzNS0wMjcxLTQ2N2UtYjA1Mi03NmM0N2ViMzliOTUiLCJ1c2VybmFtZSI6ImVtaWx5bHVjaWEuYW50b3NjaEBoYXdoYW1idXJnLmRlIiwiZmlyc3ROYW1lIjoiRW1pbHkiLCJsYXN0bmFtZSI6IkFudG9zY2gifQ.37wWnzKr02lm8RgSm01lgwq6bhaRR4rV8EPDRcvdcIA"
    })
  }).then((res) => {
    return res.json();
  }).then((response) => {
    const res = fetch("http://178.128.192.215:8000/api/container_location/", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        "Authorization": "Bearer " + response["access"]
      },
      body: JSON.stringify({
        id: "3426b1dc-3b11-4685-b8ae-723dfa593c25"
      })


    });
    console.log("Container loc are fetched!");
    return res
  })

  var locData = await locationTest.json()

  console.log("location data: ", locData)
  var data = await res2.json() // Parse the response body as JSON
  // console.log("Data check!!: ", data)

  // console.log("Container List: " + data);
  var currentDate = new Date()
  var date = currentDate.getFullYear() + '-' + (currentDate.getMonth() + 1) + '-' + currentDate.getDate() + ' ' + currentDate.getHours() + ':' + currentDate.getMinutes() + ':' + currentDate.getSeconds();
  //var curTime = currentDate.getHours() + ':' + currentDate.getMinutes() + ':' + currentDate.getSeconds();

  return {
    props: {
      containers: data,
      location: locData,
      date: date
    },
  }
}
