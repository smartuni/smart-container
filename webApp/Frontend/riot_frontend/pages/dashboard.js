import TempChart from "./temperature";
import Head from 'next/head';
import Image from 'next/image';
import Header from '../components/Header';
import LoginButton from "../components/LoginButton";
import TopCards from "@/components/TopCards";
import RecentOrders from "@/components/RecentOrders";
import {ContainersMap} from "@/components/Map/ContainersMap";
import Providers from "@/components/Providers";
//import  ContainerProblem from "./containerProblem";

export default function Home() {
  /* const storedUser = JSON.parse(localStorage.getItem('user'));
  if (storedUser){const userName = storedUser.firstName;} */

  return (
    <>
    <Head>
      <title>Create Next App</title>
      <meta name='description' content='Generated to create next app'/>
      <meta name='viewport' content='width=device-width, initial-scale=1'/>
      <link rel='icon' href='/favicon.ico'/>
    </Head>

    <main className=' bg-malibu-500 min-h-screen'>
    <div className='flex justify-between px-4 pt-4'>
      {/* <Providers><LoginButton /></Providers> */}
      <div className="ml-auto flex gap-2">
        <p className="text-sky-600">User</p>     
        <button
          className="text-blue-500 hover:underline ml-1"
          onClick={async () => {
            await signOut();
            router.push('/about');
          }}> Sign Out
        </button>
      </div>
    </div>
      
      <TopCards/>
     <div className="p-4 grid md:grid-cols-2 grid-cols-1 gap-4">
        <ContainersMap />
        <RecentOrders/>
        {/* <ContainerProblem/> */}
      </div>
    </main>
    </>
  )
}
