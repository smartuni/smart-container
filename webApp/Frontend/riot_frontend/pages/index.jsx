import Image from "next/image";
import { Inter } from "next/font/google";
import Link from "next/link";
import { useState } from "react";
import { FiMenu } from "react-icons/fi";
import css from '../styles/index.module.css'
import boatGif from '../assets/hhla-container.gif'
import cloudsGif from '../assets/sky-clouds.gif'
const inter = Inter({ subsets: ["latin"] });

export default function Home() {
  
  const [showMenu, setShowMenu] = useState(true)

  const handleNavIcon = () => setShowMenu((prev) => !prev)


  return (
    <div class="bg-scroll bg-sky-gif h-auto">
        <div className=' p-40'>
            <div className='w-full m-auto p-4 border rounded-lg bg-white overflow-y-auto h-screen items-center justify-center'>

                {/*Welcome and RIOT -------------------------------------------- */}
                <div className='px-4 pt-4'>
                    <h2 className="font-bold text-center">WELCOME</h2>
                    <h2 className="font-bold text-center">TO</h2>
                    
                    <div className="position-relative text-center">
                        <span className='font-bold text-blue-700 hover:text-blue-800 pr-10  sm:text-4xl md:text-6xl lg:text-9xl text-6xl'>R</span>
                        <span className='font-bold text-blue-600  hover:text-blue-800 pr-10  sm:text-4xl md:text-6xl lg:text-9xl text-6xl'>I</span>
                        <span className='font-bold text-blue-500  hover:text-blue-800 pr-10  sm:text-4xl md:text-6xl lg:text-9xl text-6xl'>O</span>
                        <span className='font-bold text-blue-400  hover:text-blue-800 sm:text-4xl md:text-6xl lg:text-9xl text-6xl' >T</span>
                    </div>  
                </div>
                {/*-------------------------------------------- */}
                {/*Boat Gif-------------------------------------------- */}
                <div>
                    <Image src={boatGif} class="mx-auto"/>
                </div>
                {/*-------------------------------------------- */}
                {/*Sign in and Sign up Buttons-------------------------------------------- */}
                <div className='bg-white w-96 border p-4 rounded-lg mx-auto'>
        
                    <Link href = '/signin' className="bg-blue-200 hover:bg-blue-300 flex justify-center items-center p-2 rounded-lg cursor-pointer">
                        <p className="font-bold">Sign In</p>
                    </Link>

                </div>

            

                <div className='bg-white w-96 border p-4 rounded-lg mx-auto'>
                
                    <Link href = '/contact' className="bg-blue-200 hover:bg-blue-300 flex justify-center items-center p-2 rounded-lg cursor-pointer">
                        <p className="font-bold">Sign Up</p>
                    </Link>
                </div>
                {/*-------------------------------------- */}


            </div>
        </div>
        
        
    </div>
  );
}
