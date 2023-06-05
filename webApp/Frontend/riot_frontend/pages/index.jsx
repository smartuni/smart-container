import Image from "next/image";
import { Inter } from "next/font/google";
import Link from "next/link";
import { useState } from "react";
import { FiMenu } from "react-icons/fi";
import css from '../styles/index.module.css'
import boatGif from '../assets/hhla-container-nobg.gif'
import cloudsGif from '../assets/sky-clouds.gif'
import { signIn } from "next-auth/react";


const inter = Inter({ subsets: ["latin"] });

export default function Home() {
  
  const [showMenu, setShowMenu] = useState(true)

  const handleNavIcon = () => setShowMenu((prev) => !prev)

  return (
    <div class="bg-scroll bg-sky-gif min-h-screen">
            <div className='rounded-lg'>
                <div className='pt-4'>
                    <h2 className="font-bold text-center text-3xl">WELCOME TO</h2>
                    {/* <h2 className="font-bold text-center text-3xl">TO</h2> */}
                    
                    <div className="text-center w-full">
                        <span className='font-bold text-blue-700 hover:text-blue-800 lg:pr-10 md:pr-8 sm:pr-6 pr-4 shrink sm:text-4xl md:text-6xl lg:text-9xl text-xl'>R</span>
                        <span className='font-bold text-blue-600  hover:text-blue-800 lg:pr-10 md:pr-8 sm:pr-6 pr-4 shrink sm:text-4xl md:text-6xl lg:text-9xl text-xl'>I</span>
                        <span className='font-bold text-blue-500  hover:text-blue-800 lg:pr-10 md:pr-8 sm:pr-6 pr-4  shrink sm:text-4xl md:text-6xl lg:text-9xl text-xl'>O</span>
                        <span className='font-bold text-blue-400  hover:text-blue-800 shrink sm:text-4xl md:text-6xl lg:text-9xl text-xl' >T</span>
                    </div>  
                </div>
                
                    <div className= "absolute ml-20 inset-x-0 bottom-0"> 
                
                        {/*Welcome and RIOT -------------------------------------------- */}
                    
                        {/*-------------------------------------------- */}
                        {/*Boat Gif-------------------------------------------- */}
                        <div>
                            <Image src={boatGif} class="mx-auto"/>
                        </div>
                    {/*-------------------------------------------- */}
                    {/*Sign in and Sign up Buttons-------------------------------------------- */}
                    <div className="flex items-center justify-center">
                        <div className='bg-malibu-500 w-1/3 p-4 rounded-lg'>
                            <button className="bg-blue-200 w-full hover:bg-blue-300 flex justify-center font-bold items-center lg:p-4 p-2 rounded-lg" onClick={() => signIn()}>
                                Sign In
                            </button>
                        </div>
                    </div>
            
                    <div className="flex items-center justify-center">
                        <div className='bg-malibu-500 w-1/3 p-4 rounded-lg'>
                
                            <Link href = '/signup' className="bg-blue-200 hover:bg-blue-300 flex justify-center items-center lg:p-4 p-2 rounded-lg cursor-pointer ">
                                <p className="font-bold">Sign Up</p>
                            </Link>

                        </div>
                    </div>
                    {/*-------------------------------------- */}

                

                </div>
                
            </div>
        
        
    </div>
  );
}
