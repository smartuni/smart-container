import '/styles/globals.css'
import Sidebar from '../components/Sidebar'
import { NextUIProvider } from '@nextui-org/react'

export default function App({ Component, pageProps }) {
  return (
    <NextUIProvider>
      <Sidebar>
        <Component {...pageProps} />
      </Sidebar>
    </NextUIProvider>
  )
}
