import TempChart from "./temperature";
import Head from 'next/head';
import Image from 'next/image';
import Header from '../components/Header';
import TopCards from "@/components/TopCards";
import BarChart from "@/components/BarChart";
import RecentOrders from "@/components/RecentOrders";
// import Map from "@/components/Map/Map";

const DEFAULT_CENTER = [38.907132, -77.036546]

export default function Home() {


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
      <div className="p-4 grid md:grid-cols-3 grid-cols-1 gap-4">


      {/* <Map  width="800" height="400" center={DEFAULT_CENTER} zoom={12}>
            {({ TileLayer, Marker, Popup }) => (
              <>
                <TileLayer
                  url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
                  attribution="&copy; <a href=&quot;http://osm.org/copyright&quot;>OpenStreetMap</a> contributors"
                />
                <Marker position={DEFAULT_CENTER}>
                  <Popup>
                    A pretty CSS3 popup. <br /> Easily customizable.
                  </Popup>
                </Marker>
              </>
            )}
          </Map> */}

        <RecentOrders/>
      </div>
    </main>
    </>
  )
}
