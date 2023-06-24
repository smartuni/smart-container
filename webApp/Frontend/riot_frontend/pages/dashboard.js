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
          <RecentOrders contaienrs={props.containers} />
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

  console.log("Containers are fetched!");
  const res = await fetch("http://178.128.192.215:8000/api/container/", {
    method: "GET",
    headers: {
      "Content-Type": "application/json",
      "Authorization": "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ0b2tlbl90eXBlIjoiYWNjZXNzIiwiZXhwIjoxNjg3NjQzNDAwLCJpYXQiOjE2ODc2NDMxMDAsImp0aSI6ImY3YWE5NmIyOWU5NTRiMTE5ODkyYmVmMzM2N2MwOTZmIiwidXNlcl9pZCI6ImQwNjk5MTM1LTAyNzEtNDY3ZS1iMDUyLTc2YzQ3ZWIzOWI5NSIsInVzZXJuYW1lIjoiZW1pbHlsdWNpYS5hbnRvc2NoQGhhd2hhbWJ1cmcuZGUiLCJmaXJzdE5hbWUiOiJFbWlseSIsImxhc3RuYW1lIjoiQW50b3NjaCJ9.56HcUR2LFJ6Y-DPxDkCdVqs3YUKU1D8I9IgpPmMtbIM"
    },

  });
  var data = await res.json() // Parse the response body as JSON

  // const res_array = []
  // for (let i in data) {
  //   res_array.push([data[i]]);
  // }

  console.log("Container List: " + data);

  return {
    props: {
      containers: data,

    },
  }
}
