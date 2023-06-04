import { SessionProvider } from "next-auth/react";
import React from "react";

function Providers({ children }) {
  return <SessionProvider>{children}</SessionProvider>;
}

export default Providers;
