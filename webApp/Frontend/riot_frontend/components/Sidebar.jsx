import React from 'react'
import Link from 'next/link'
import Image from 'next/image'
import {RxSketchLogo, RxDashboard, RxPerson} from 'react-icons/rx'
import {HiOutlineShoppingBag} from 'react-icons/hi'
import { FiSettings } from 'react-icons/fi'
import { AiOutlineInfoCircle, AiOutlinePhone, AiOutlineHome } from 'react-icons/ai'
import { BiMap } from 'react-icons/bi'
import myLogo from '../assets/RIOT_Sum_2023_Logo.png'
const Sidebar = ({ children }) => {
    return (
        <div className='flex'>
            <div className='fixed w-20 h-screen p-4 bg-white border-r-[1px] flex flex-col justify-between'>
                <div className='flex flex-col items-center'>
                    <Link href='/'>
                        <div className='bg-blue-200 hover:bg-blue-300 text-white p-3 rounded-lg inline-block'>
                        <AiOutlineHome size={20}/>
                        </div>
                    </Link>
                    <span className='border-b-[1px] border-gray-200 w-full p-2'></span>
                    <Link href='/dashboard'>
                        <div className='bg-gray-100 hover:bg-gray-200 cursor-pointer my-4 p-3 rounded-lg inline-block'>
                            <RxDashboard size={20}/>
                        </div>
                    </Link>
                    {/* <Link href='/customers'>
                        <div className='bg-gray-100 hover:bg-gray-200 cursor-pointer my-4 p-3 rounded-lg inline-block'>
                            <RxPerson size={20}/>
                        </div>
                    </Link>
                    <Link href='/orders'>
                        <div className='bg-gray-100 hover:bg-gray-200 cursor-pointer my-4 p-3 rounded-lg inline-block'>
                            <HiOutlineShoppingBag size={20}/>
                        </div>
                    </Link> */}
                    <Link href='/map'>
                        <div className='bg-gray-100 hover:bg-gray-200 cursor-pointer my-4 p-3 rounded-lg inline-block'>
                            <BiMap size={20}/>
                        </div>
                    </Link>
                    <Link href='/about'>
                        <div className='bg-gray-100 hover:bg-gray-200 cursor-pointer my-4 p-3 rounded-lg inline-block'>
                            <AiOutlineInfoCircle size={20}/>
                        </div>
                    </Link>
                    <Link href='/contact'>
                        <div className='bg-gray-100 hover:bg-gray-200 cursor-pointer my-4 p-3 rounded-lg inline-block'>
                            <AiOutlinePhone size={20}/>
                        </div>
                    </Link>
                </div>
            </div>
            <main className='ml-20 w-full'>{children}</main>

        </div>


    )
 }
 export default Sidebar