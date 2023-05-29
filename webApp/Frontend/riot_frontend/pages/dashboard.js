import TempChart from "./temperature";
import Head from 'next/head';
import Image from 'next/image';
import Header from '../components/Header';
import TopCards from "@/components/TopCards";
import RecentOrders from "@/components/RecentOrders";
import {ContainersMap} from "@/components/Map/ContainersMap";
import  ContainerProblem from "./containerProblem";

export default function Home() {

//const data  = axios.get(`/localhost/${}`)

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
      <TopCards/>
      <div className="p-4 grid md:grid-cols-2 grid-cols-1 gap-4">
        <ContainersMap />
        <RecentOrders/>
        <ContainerProblem/>
      </div>
    </main>
    </>
  )
}
