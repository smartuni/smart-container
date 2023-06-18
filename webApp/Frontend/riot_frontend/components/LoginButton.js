"use client";
import { signIn, signOut, useSession } from "next-auth/react";
import React from "react";
import { useRouter } from 'next/router';


const LoginButton = () => {
  const { data: session } = useSession();
  const router = useRouter();
  const storedUser = JSON.parse(localStorage.getItem('user'));
  const userName = storedUser.firstName;

  return (
    <div className="ml-auto flex gap-2">
      {session?.user ? (
        <>
          {/* <p className="text-sky-600"> {session.user.firstName}</p> */}
          <p className="text-sky-600"> {userName}</p>
          <button
            className="text-blue-500 hover:underline ml-1"
            onClick={async () => {
              await signOut();
              router.push('/about');
            }}> Sign Out
          </button>

        </>
      ) : (
        <button className="text-blue-500 hover:underline ml-1" onClick={() => signIn()}>
          Sign In
        </button>
      )}
    </div>
  );
};

export default LoginButton;
