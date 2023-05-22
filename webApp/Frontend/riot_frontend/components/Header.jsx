import React from 'react'
import Link from 'next/link'
const Header = () => {
    return (
        <div className='flex justify-between px-4 pt-4'>
            <h2>Dashboard</h2>
            <h2>Welcome back, Team!
                <span> |  
                    <Link className="text-blue-500 hover:underline" href="/#">Log out</Link>
                </span>
            </h2>

            
        </div>
    )
}
export default Header