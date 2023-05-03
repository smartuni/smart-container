import Image from "next/image";
import { Inter } from "next/font/google";
import Link from "next/link";
import { useState } from "react";
import { FiMenu } from "react-icons/fi";
import css from '../styles/index.module.css'




const inter = Inter({ subsets: ["latin"] });

export default function Home() {

  const [showMenu, setShowMenu] = useState(true)

  const handleNavIcon = () => setShowMenu((prev) => !prev)


  return (
    <main className="flex min-h-screen flex-col items-center justify-between p-24">

      <button onClick={handleNavIcon} className={css.nav_size}><FiMenu />  </button>


      <nav className={css.navbar} style={{ display: showMenu ? 'flex' : 'none' }}>
        <ul>
          <li>
            <a href="#">Home</a>
          </li>
          <li>
            <a href="/about">About Us</a>
          </li>
          <li>
            <a href="/contact">Contact</a>
          </li>
          <li>
            <a href="/signup">Sign up</a>
          </li>
          <li>
            <a href="/map/page">To Map Page</a>
          </li>
        </ul>
      </nav>

      <div className="mb-32 grid text-center lg:mb-0 lg:grid-cols-4 lg:text-left">


        <div className={css.container}>
          <a href="/signup">
            <button className={css.create_account}>Create Account</button>
          </a>
        </div>


      </div>
    </main>
  );
}
