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

// In the fetch request, create variable that stores the current time
//    when the fetch is successful. This variable will then be 
//    in the "Last Fetched: ----" header


export default function Home() {
  const containers = useContainers()



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
        <TopCards />
        <div className="p-4 grid md:grid-cols-2 grid-cols-1 gap-4">
          <ContainersMap containers={containers} />
          <RecentOrders containers={containers} />
          {/* <ContainerProblem/> */}
        </div>
      </main>
    </>
  )
}
