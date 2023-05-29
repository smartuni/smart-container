import '/styles/globals.css'
import Sidebar from '../components/Sidebar'
import '../data/container.js';

export default function App({ Component, pageProps }) {
  return (
    <Sidebar>
    <Component {...pageProps} />
    </Sidebar>
  )
}
