"use client";
import { signIn, signOut, useSession } from "next-auth/react";
import React from "react";

const LoginButton = () => {
  const { data: session } = useSession();
  return (
    <div className="ml-auto flex gap-2">
      {session?.user ? (
        <>
          <p className="text-sky-600"> {session.user.name}</p>
          <button className="text-blue-500 hover:underline ml-1" onClick={() => signOut()}>
            Sign Out
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
