import TempChart from "./temperature";
import Head from 'next/head';
import Image from 'next/image';
import Header from '../components/Header';
import TopCards from "@/components/TopCards";
import BarChart from "@/components/BarChart";
import RecentOrders from "@/components/RecentOrders";
import Map from "@/components/Map/Map";

const DEFAULT_CENTER = [53.5511, 9.9937];
const markers = [
  { name: 'Container 1', location: [53.55587, 10.02439] },
  { name: 'Container 2', location: [53.55513463677272, 9.992930792175889] },
  { name: 'Container 3', location: [53.53952514227034, 10.0049117958243] },
];

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
      <div className="p-4 grid md:grid-cols-2 grid-cols-1 gap-4">
        <Map  width="100%" height="400" center={DEFAULT_CENTER} zoom={12}>
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
        </Map>
        <RecentOrders/>
      </div>
    </main>
    </>
  )
}
