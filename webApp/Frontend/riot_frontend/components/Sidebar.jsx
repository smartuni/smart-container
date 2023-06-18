import React from 'react'
import Link from 'next/link'
import Image from 'next/image'
import {RxDashboard} from 'react-icons/rx'

import { AiOutlineInfoCircle, AiOutlinePhone} from 'react-icons/ai'
import { ImHome } from 'react-icons/im'
import { BiMap } from 'react-icons/bi'

const Sidebar = ({ children }) => {
    return (
        <div className='flex'>
            <div className='fixed w-20 h-screen p-4 bg-white border-r-[1px] flex flex-col justify-between'>
                <div className='flex flex-col items-center'>
                    <Link href='/'>
                        <div className='bg-blue-200 hover:bg-blue-300 text-gray-700 p-3 rounded-lg inline-block'>
                        <ImHome size={20}/>
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
                    <Link href='/signin'>
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