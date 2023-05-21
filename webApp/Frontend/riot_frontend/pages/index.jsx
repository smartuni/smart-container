import Image from "next/image";
import { Inter } from "next/font/google";
import Link from "next/link";
import { useState } from "react";
import { FiMenu } from "react-icons/fi";
import css from '../styles/index.module.css'
import boatGif from '../assets/vessel-fishing.gif'

const inter = Inter({ subsets: ["latin"] });

export default function Home() {
  
  const [showMenu, setShowMenu] = useState(true)

  const handleNavIcon = () => setShowMenu((prev) => !prev)


  return (
    <div className='bg-gray-100 min-h-screen'>
        <div className='p-4'>
            <div className='w-full m-auto p-4 border rounded-lg bg-white overflow-y-auto'>

                <div className='px-4 pt-4'>
                    <h2 className="font-bold text-center">Welcome to </h2>
                    
                        <div className="position-relative text-center">
                            <span className='font-bold text-blue-700 pr-10  sm:text-4xl md:text-6xl lg:text-9xl text-6xl'>R</span>
                            <span className='font-bold text-blue-600  pr-10  sm:text-4xl md:text-6xl lg:text-9xl text-6xl'>I</span>
                            <span className='font-bold text-blue-500  pr-10  sm:text-4xl md:text-6xl lg:text-9xl text-6xl'>O</span>
                            <span className='font-bold text-blue-400  sm:text-4xl md:text-6xl lg:text-9xl text-6xl' >T</span>
                        </div>  
                </div>
                <div>
                    <Image src={boatGif} class="mx-auto"/>
                </div>
            </div>
        </div>
        
        
    </div>
  );
}
