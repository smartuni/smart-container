import '/styles/globals.css'
import Sidebar from '../components/Sidebar'
import { useRouter } from 'next/router';


export default function App({ Component, pageProps }) {
  const router = useRouter();
  const excludedPages = ['/signin', '/signup'];
  const isExcludedPage = excludedPages.includes(router.asPath);

  return (
    <>
      {isExcludedPage ? (
        <Component {...pageProps} />
      ) : (
        <>
          <Sidebar >
          <Component {...pageProps} />
          </Sidebar>
        </>
      )}
    </>
  )
}
