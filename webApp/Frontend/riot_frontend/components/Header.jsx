import React from 'react'
//import Link from 'next/link'
import { useEffect, useState } from "react";
import { useRouter } from "next/router";

const Header = () => {
    const router = useRouter();
    const [user, setUser] = useState(null);
    useEffect(() => {
        const storedUser = localStorage.getItem('localuser');
        if (storedUser) {
        setUser(JSON.parse(storedUser));
        }
    }, []);

    const signOut = () => {
        // Remove the user token from localStorage
        localStorage.removeItem("localuser");
        // Redirect to the desired page
        router.push("/");
    };

    return (
        <div className='flex justify-between px-4 pt-4'>
            <div className="ml-auto flex gap-2">
                {user ? (
                <p className="text-sky-600">Welcome, {user.firstName}!</p>
                ) : (
                <p className="text-sky-600">Welcome, user!</p>
                )}
                {user ? (
                <button className="text-blue-500 hover:underline ml-1" onClick={signOut}> Sign Out</button>
                ) : (
                <a className="text-blue-500 hover:underline ml-1" href="/signin_page">Sign in</a>
                )}
                
            </div>       
        </div>
    )
}
export default Header